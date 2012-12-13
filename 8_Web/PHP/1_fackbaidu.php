<html>
<head>
	<title> fake baidu</title>
</head>

<body>
	<h1 align="center">Fack baidu</h1>


<form name="fack_baidu" method="get" action="http://www.baidu.com/s">
	<!-- 
	<table width"352" border"0" cellpadding="0" cellspacign="0">
	-->
	<div align="center">
	<table>
	<tr>
		<input type="text" name="wd">
		<input type="submit" name="su" value="fake baidu">
		&nbsp;
		</td>
	</tr>
	</table>
	</div>
</form>


<form name="login" method="get" action="">
	<div align="center">
	<table>
		this would be use get method to communicate with web site.
		<br />
	<tr>
		name:
		<input type="text" name="name" id="name">
		Password:
		<input type="password" name="pwd" id="pwd">
		<input type="submit" name="submit" value="login" id="submit">
		</td>
	</tr>
	</table>
	</div>
</form>

<form name="shopping" method="post" action="">
	<div align="center">
	<table>
		this would be use post method to communicate with web site.
		<br />
	<tr>
		shopping list:
		<input type="text" name="shopping_list" id="shopping_lsit">
		Credit Card ID:
		<input type="password" name="Card_ID" id="Card_ID"> 
		<input type="submit" name="buy" value="BuyNOW" id="buy">
		</td>
	</tr>
	</table>
	</div>
</form>

<?php
	//echo"php script";
	if( $_POST[buy]=="BuyNOW") //in form1, user log in
	{
		//echo"get the post";
		echo"you intyped shopping list:".$_POST[shopping_list].";<br\>password is:".$_POST[Card_ID];
	}

?>
</body>
</html>
