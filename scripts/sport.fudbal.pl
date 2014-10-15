#######################################################################
# THIS SCRIPT IS DOWNLOADING ARTICLES FOR THE SPCIFIED RANGE OF DATES #
#######################################################################

#######################################################################
# INFO.HRONIKA														  #
#######################################################################

# NOTE: currently the b92 has links that looks like this

# with this line i can run my perl program as an executable
#!/usr/local/bin/perl -w
use strict;
use WWW::Mechanize;
use base qw(HTML::TagParser);

use Encode;

use Date::Calc qw(Today Delta_Days Add_Delta_Days );

# open links.txt file which contains info about links that are already downloaded
# NOTE: +< means that file is opened both for read and writing and creates the file if it doesn't exist
my @all_category_links = ();

print "Checking if there is a links file...\n";

if (open(LINKS, '<','../corpus/sport.fudbal/links'))
{
	while (my $line = <LINKS>)
	{
		# NOTE: deletes last char only if its newline character
		chomp($line);
		push(@all_category_links, $line);
	}
	close(LINKS);
}


# Initialize mech...
my $mech = WWW::Mechanize->new();

# $mech->proxy(['http', 'ftp'], 'http://proxy-1.pstech.rs:3128');
my $file_number = 0;

print "Setting the start date...\n";

my @start_date = (2014,1,1);
my @stop_date  = Today();
my $j = Delta_Days(@start_date, @stop_date);

for (my $i = 0; $i <= $j; $i++ )
{
	my @date = Add_Delta_Days(@start_date, $i);
	my ($year, $month, $day) = @date;
	# http://www.b92.net/sport/fudbal/vesti.php?yyyy=2014&mm=05&dd=17&nav_id=849312
	my $url = "http://www.b92.net/sport/fudbal/vesti.php?yyyy=".$year."&mm=".$month."&dd=".$day;
	
	print "Fetching the link for a given date...\n";
	
	$mech->get( $url );
	#TODO: Date format problem
	if ($month < 10)
	{
		$month = "0".$month;
	}
	if ($day < 10)
	{
		$day = "0".$day;
	}
	# print $month." ".$day."\n";

	print "Fetching all the links connected to the previous one...\n";

	my @current_page_links = $mech->find_all_links( url_regex => qr/^\/sport\/fudbal\/vesti.php\?yyyy=$year\&mm=$month\&dd=$day/);
	for my $link ( @current_page_links ) {
		my $current_link = $link->url_abs;
		print $current_link."\n";
		# &version=print problem!
		$current_link =~ s/&version=print//;
		if (not (grep $_ eq $current_link, @all_category_links) or not @all_category_links)
		{
			print "Download page...\n";
			
			push(@all_category_links, $current_link);
			open(LINKS, '+>>', '../corpus/sport.fudbal/links') or die "Cannot open links file!\n";
			print LINKS $current_link."\n";
			close(LINKS);
			&download_page($current_link);
		}
	}
}


######################################################################################  

sub download_page
{
	my ($url) = shift;
	# timeout in seconds
	sleep 1;
	$mech->get( $url );

	my $page = $mech->content;

	# $page was in cp1250 encoding but it seems that Mechanize already did decode('cp1250', $page) for us.
	# Because of that we need just to encode before we write that in a file. 
	# But...... read the rest of the comments about HTML::TagParser module

	# HTML::TagParser natively understands the character encoding used in document by parsing its meta element.
	# and the parsed text is converted to UTF-8
	# Because of that we need to encode decoded page back into encoding that page was using before it was decoded by Mechanize.
	# So, we need to know the encoding of the page
	
	# <meta http-equiv="Content-Type" content="text/html; charset=windows-1250"/>
	my $encoding = "cp1250";
	if ($page =~ /<meta\s+.*content\s*=\s*\".*charset\s*=\s*(.*)\"/)
	{
	    $encoding = $1;
	}

	my $page_encoded = encode($encoding, $page);
	my $html = HTML::TagParser->new($page_encoded);
	# Date
	my $date = "";
	my @span = $html->getElementsByTagName( "span" );
	foreach my $span_iter (@span) {
		my $span_attr = $span_iter->attributes;
		my $span_attr_class = $span_attr->{"class"};
		if ($span_attr_class and $span_attr_class eq "article-info1")
		{
			print "nasao article-info1\n";
			$date = $span_iter->innerText();
			if ($span_iter->innerText() =~ /(.*)\|(.*)/)
			{
				print "matchovao regex\n";
				$date = "$1";
			}
		}
	}
	
	my @div = $html->getElementsByTagName( "div" );
	my $subhtml = HTML::TagParser->new();
	foreach my $div_iter (@div) {
		my $div_attr = $div_iter->attributes;
		my $div_attr_class = $div_attr->{"class"};
		if ($div_attr_class and $div_attr_class eq "article-text")
		{
				$subhtml = $div_iter->subTree();
		}
	}

	my $h = $subhtml->getElementsByTagName( "h1" );
	my $caption = $h->innerText();

	# # article b92 ex1: <p class="sms"> Fudbaleri Crvene zvezde plasirali su se u plej-of za plasman</p>
	# # article b92 ex2: <p>Revan je kao i prvi meè zavren bez golova, nije ih bilo </p>
	my @p = $subhtml->getElementsByTagName("p");

	my $text;
	foreach my $p_iter (@p) {
		$text .= $p_iter->innerText();
		$text .= "\n";	
	}

	&text_correction($text);
	
	$file_number++;
	my $file_name = "article_".$file_number.".txt";
	open(FH, ">../corpus/sport.fudbal/$file_name") or die "Cannot create file!\n";
	
	my $header_source = "> Izvor: B92\n";
	my $header_date = "> Datum: ";
	my $header_group = "> Rubrika: sport.fudbal\n";
	my $header_caption = "> Naslov: ";
	my $header_article = "> Članak:\n\n";
	
	print FH $header_source.$header_date;
	print FH $date."\n";
	print FH $header_group.$header_caption;
	print FH $caption."\n";
	print FH $header_article;
	print FH $text;
 	
	close(FH);
}

sub text_correction
{
	# very risky!!!
	$_[0] =~ s/Izvor: .*//;
	$_[0] =~ s/Foto: .*//;
	
	# Piše: Slobodan Bubnjević
	# $_[0] =~ s/Pi: .*//;


	# double space
	$_[0] =~ s/ +/ /g;
	$_[0] =~ s/\t+/ /g;
	# punct space
	$_[0] =~ s/\s+\.\s+/. /g;
	$_[0] =~ s/\s+\,\s+/, /g;
	$_[0] =~ s/\s+\?\s+/? /g;
	$_[0] =~ s/\s+\!\s+/! /g;
	$_[0] =~ s/\s+\:\s+/: /g;
	$_[0] =~ s/\s+\;\s+/; /g;
	$_[0] =~ s/\(\s+/(/g;
	$_[0] =~ s/\s+\)/) /g;

	# space dash space
	$_[0] =~ s/ +\- +/ - /g;

	# &bdquo; &ldquo; &rdquo;
	$_[0] =~ s/&bdquo;/"/g;
	$_[0] =~ s/&edquo;/"/g;
	$_[0] =~ s/&ldquo;/"/g;
	$_[0] =~ s/&rdquo;/"/g;
	$_[0] =~ s/&laquo;/"/g;
	$_[0] =~ s/&raquo;/"/g;

	# &ndash;
	$_[0] =~ s/&ndash;/-/g;
	# &nbsp;
	$_[0] =~ s/&nbsp;//g;
	# &ordm;
	$_[0] =~ s/&ordm;//g;
	# t&#242;
	$_[0] =~ s/t&#\d+;//g;
	
	# &frac12;
	$_[0] =~ s/t&#\d+;//g;

	# general rule
	$_[0] =~ s/&.+;//g;

	# general rule 2
	$_[0] =~ s/t&#.+;//g;

}