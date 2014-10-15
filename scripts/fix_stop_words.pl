#!/usr/bin/perl -w

@files = <*>;
foreach $file (@files) {
 	if ($file ne "fix_stop_words.pl" and $file ne "config")
 	{
 		print $file."\n";
 			
	 	open (FILE, "<$file") or die "Can't open $file: $!\n";
		@lines = <FILE>;
		close FILE;
		
		#Open same file for writing, reusing STDOUT
		open (FH, ">$file") or die "Can't open $file: $!\n";

		#Walk through lines, putting into $_, and substitute 2nd away
		for ( @lines ) {
			$line = $_;
			&text_correction($line);
			print FH $line;
		}
		#Finish up
		close FH;
	}
}

sub text_correction
{
	
	$_[0] =~ s/zx/ž/g;
	$_[0] =~ s/cx/ć/g;
	$_[0] =~ s/cy/č/g;
	$_[0] =~ s/nx/nj/g;
	$_[0] =~ s/dy/dž/g;
	$_[0] =~ s/lx/lj/g;
	$_[0] =~ s/sx/š/g;
	$_[0] =~ s/dx/đ/g;

	$_[0] =~ s/Zx/Ž/g;
	$_[0] =~ s/Cx/Ć/g;
	$_[0] =~ s/Cy/Č/g;
	$_[0] =~ s/Nx/Nj/g;
	$_[0] =~ s/Dy/Dž/g;
	$_[0] =~ s/Lx/Lj/g;
	$_[0] =~ s/Sx/Š/g;
	$_[0] =~ s/Dx/Đ/g;

	$_[0] =~ s/ZX/Ž/g;
	$_[0] =~ s/CX/Ć/g;
	$_[0] =~ s/CY/Č/g;
	$_[0] =~ s/NX/NJ/g;
	$_[0] =~ s/DY/DŽ/g;
	$_[0] =~ s/LX/LJ/g;
	$_[0] =~ s/SX/Š/g;
	$_[0] =~ s/DX/Đ/g;

}