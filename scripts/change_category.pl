 #!/usr/bin/perl -w
 
 @files = <*>;
 foreach $file (@files) {
 	if ($file ne "change_category.pl" and $file ne "links")
 	{
 		print $file."\n";
	 	open (FILE, "<$file") or die "Can't open $file: $!\n";
		@lines = <FILE>;
		close FILE;
		
		#Open same file for writing, reusing STDOUT
		open (STDOUT, ">$file") or die "Can't open $file: $!\n";

		#Walk through lines, putting into $_, and substitute 2nd away
		for ( @lines ) {
			s/Rubrika: život.sex/Rubrika: život_sex/;
			print;
		}
		#Finish up
		close STDOUT;
	}
}
