<?php

if ( isset($_GET['status']) )
{
	/*open the status file*/
	$myfile = fopen("status.txt","w");
	
	if( $_GET[status]=='on' )
	{
		/*write the status*/
		fwrite( $myfile , '1' );
		echo("LED ON");
		header("Location: on.html");
	}
	else if( $_GET[status]=='off' )
	{
		fwrite( $myfile , '0' );
		echo("LED OFF");
		header("Location: off.html");
	}
	
	fclose($myfile);
}


?> 