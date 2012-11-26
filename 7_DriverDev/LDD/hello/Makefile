obj-m := hello.o
#KERNELDIR = /lib/modules/2.6.35.13/build
KERNELDIR = /lib/modules/3.2.0-23-generic-pae/build
INSTALLDIR = /home/tucan/7_DriverDev/LDD/install 
PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	cp hello.ko $(INSTALLDIR)
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions
	.PHONY: modules modules_install clean
	#$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
