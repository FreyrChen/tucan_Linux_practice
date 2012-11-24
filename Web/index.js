
<script type="text/javascript">
<!--
/**** detect user's web browser version ***/
function detect_browser()
{
	var browser=navigator.appName
	var b_version=navigator.appVersion
	var version=parseFloat(b_version)
	
	alert("Browser name:"+browser+"\nBrowser version:"+version)
	//document.write("<br />")
	//document.write("Browser version:"+version)
}


/******************************************/
function getCookie(c_name)
{
	if( document.cookie.length > 0)
	{
		c_start = document.cookie.indexOf( c_name+"=" )
		if( c_start!= -1 )
		{
			c_start = c_start + c_name.length + 1
			c_end = document.cookie.indexOf(";", c_start)
		}
	}
}

/*** set cookie to store user's info ****/
function setCookie( c_name, value, expiredays )
{
	var exdate = new Date()
	exdate.setDate( exdate.getDate()+expirdays)
	document.cookie=c_name+"=" + escape(value)
}

-->
