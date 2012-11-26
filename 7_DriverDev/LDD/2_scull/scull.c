//******************************************************************************
//file: 2_scull.c
//author: tusion@163.com	date: 2012/07/08
//usege: this is a sample character device run on Linux, 
//	just simulate a buffer which store in the memory, 
//	used  open/close device, read and open device;
//*******************************************************************************

#include <linux/module.h>
#include <linux/fs.h>		// struct file_operations()
#include <linux/kernel.h>	//container_of()
#include <linux/slab.h>	  	// kmalloc(), kfree(),
#include <linux/errno>
#include <asm/uaccess.h>
#include <linux/cdev.h>		//struct cdev

// intial file_oprations struct
struct file_oprations scull_fops =
{
	.owner 	= THIS_MODULE;
	.llseek = scull_llseek,
	.read 	= scull_read,
	.write	= scull_write,
	.ioctl	= scull_ioctl,
	.open	= scull_open,
	.release = scull_release,
};

//	
struct scull_dev { 
				 struct scull_qset *data;  	/* Pointer to first quantum set */ 
				 int quantum;  				/* the current quantum size */ 
				 int qset;  				/* the current array size */ 
				 unsigned long size;  		/* amount of data stored here */ 
				 unsigned int access_key;  	/* used by sculluid and scullpriv */ 
				 struct semaphore sem;  	/* mutual exclusion semaphore  */ 

				 struct cdev cdev; 			/* Char device structure */
				};



struct scull_qset{
			void 	**data;
			struct 	scull_qset	*next;
		 };

//******************************************************************************
//******************************************************************************
static void scull_setup_cdev( struct scull_dev *dev, int index )
{
	int err;
	int devno = MEKDEV( scull_major, scull_minor+index );
	
	cdev_init( &dev->cdev, &scull_fops );
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops	= &scull_fops;
	err = cdev_add( &dev->cdev, devno, 1 );
	// fial
	if( err )
		printk(KERN_NOTICE "Error %d adding scull %d ", err, index );
}

//******************************************************************************
// open
//******************************************************************************
int scull_open( struct inode *inode, struct file *filp )
{
	struct scull_dev *dev;			//device information
	// usr the macro can get the whole struct of scull_dev from cdev.	
	dev = container_of( inode->i_cdev, struct scull_dev, cdev );
	filp->private_data = dev;
	//now trim to o the length of the device if open was write-only
	if( (filp->f_flag & O_ACCMODE ) == O_WRONLY )
		scull_trim( dev );
	return 0;
} 

//******************************************************************************
//******************************************************************************
sszie_t scull_read( struct file *file, char __user *buf, szie_t count, loff_t *f_pos )
{
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int 	quantum = dev->quantum, qset = dev->qset;
	int 	intemsize = quantum *qset;	// this intem has char szie
	int 	item,s_pose, q_pos, rest;
	ssize_t	retval = 0;
	
	if( down_interruptible( &dev->sem ) )
		return -ERESTARTSYS;
	if( *f_pos >= dev->size )
		goto out;
	if( * f_pos + count > dev->size )
		count = dev->size - *f_pos;
	
	/* find listitem, qset index, and offset in the quantum */
	item = ( long ) *f_pos / itemsize;
	rest = ( long ) *f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;
	
	 /* follow the list up to the right position (defined elsewhere) */
	dptr = scull_follow( dev, item );
	
	if( dptr == NULL || !dptr->data || !dptr->data[s_pos])
		goto out;
	
	/* read only up to the end of this quantum */
	if( count > quantum - q_pos )
		count = quantum - q_pos;
	if( copy_to_user( buf, dptr->data[s_pos] + q_pos, count ))
	{
		retval = -EFAULT;
		goto out;
	}
	*f_pos += count;
	retval = count;
	
   out:
	up( &dev->sem );
	return retval;
}

//******************************************************************************
// release, close function may be call release
//******************************************************************************
ssize_t scull_write( struct file *filp, const char __user *buf, size_t count, lofft_t *fpos )
{
	struct scull_dec *dev = filp->private_data;
	struct scull_qset *dptr;
	int		quantum = dev->quantum,
	int 	qset = dev->qset;
	int		itemsize = quantum * qset;
	int 	item, s_pos, q_pos, rest;
	ssize_t	retval = -ENOMEM;

	if( down_interruptible( &dev->sem )
		return -ERESTARTSYS;
		
	/* find listitem, qset index and offset in the quantum */
	item = ( long ) *f_pos / itemsize;
	rest = ( long ) *f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;
	
	 /* follow the list up to the right position */
	dptr = scull_follow( dev, item );
	if( dptr == NULL )
		goto out;
	if( !dptr->data )
	{
		dptr->data = kmalloc( qset * sizeof( char * ), GFP_KERNEL );
		if( !detr->data )
			goto out;
		memset( dptr->data, 0, qset * sizeof( char * ) );
	}

	if( !dptr->data[s_pos] )
	{
		dptr->data[s_pos] =kmalloc( quantum, GFP_KERNEL);
		if( !dptr->data[s_pos] )
			goto out;
	}

	/* write only up to the end of this quantum */
	if( count > quantum - q_pos )
		count = quantum - q_pos;
	if( copy_from_user( dptr->data[s_pos]+q_pos, buf, count ) )
	{
		retval = -EFAULT;
		goto out;	  
	}
	*f_pos += count;
	retval =  count;

	if( dev->size < *f_pos )
		dev->size = *f_pos;
	
  out:
	up( &dev->sem );
	return retval;
}
//******************************************************************************
// release, close function may be call release
//******************************************************************************
int scull_release( struct inode *inode, struct file *filp )
{
	return 0;
}


//******************************************************************************
// go throgh the list and free all list member
//******************************************************************************
int scull_trim( struct scull_dev *dev )
{
	struct scull_qset *next, *dptr;
	int 	qset = dev->qset;
	int	i;
	
	for( dptr = dev->data; dptr; dptr = next )
	{
		//go through the list
		if( dptr->data )
		{	
			for( i=0; i<qset; i++ )
				kfree( dptr->data[i];
			kfree( dptr->data );
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree( dptr );
	}
	dev->size = 0;
	dev->quantum = scull_quantunm;
	dev->qset = scull_qset;
	dev->data = NULL;
	
	return 0;
}

//******************************************************************************
//auto detect the device ID	 LDD P52
//*****************************************************************************
if( scull_major )
{	//if device ID is sure 
	dev = MKEDV( scull_major, scull_minor );
	result = register_chrdec_region( dev, scull_nr_devs, "scull");
else
{	//
	result = alloc_chrdev_region( &dev, scull_minor, scull_nr_devs, "scull" );
	scull_major = MAJOR( dev );
}
if( result < 0 )
{
	printk( KERN_WARING "scull: can't get major %d\n", scull_major );
	return result;
}





