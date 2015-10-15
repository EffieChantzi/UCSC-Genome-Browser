# shortFrags.sql was originally generated by the autoSql program, which also 
# generated shortFrags.c and shortFrags.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#CSHL transfrags format (BED 6+)
CREATE TABLE cshlShortTransfrag (
    chrom varchar(255) not null,	# Reference sequence chromosome or scaffold
    chromStart int unsigned not null,	# Start position in chromosome
    chromEnd int unsigned not null,	# End position in chromosome
    name varchar(255) not null,	# Name of item
    score int unsigned not null,	# Score from 0-1000
    strand char(1) not null,	# + or -
    length int unsigned not null,	# contig's length (number of covered bases = end - start)
    numUnique int unsigned not null,	# number of unique sequences in this contig
    numReads int unsigned not null,	# total reads count in this contig
    minSeqCount int unsigned not null,	# minimum sequence-count value
    maxSeqCount int unsigned not null,	# maximum sequence-count value
    aveSeqCount float not null,	# average seqeunce-count value
    firstSeqCount int unsigned not null,	# first-quartile sequence-count value
    medSeqCount int unsigned not null,	# median sequence-count value
    thirdSeqCount int unsigned not null,	# third-quartile sequence-count value
    minReadCount int unsigned not null,	# minimum reads-count value
    maxReadCount int unsigned not null,	# maximum reads-count value
    aveReadCount float not null,	# average seqeunce-count value
    firstReadCount int unsigned not null,	# first-quartile reads-count value'
    medReadCount int unsigned not null,	# median reads-count value
    thirdReadCount int unsigned not null,	# third-quartile reads-count value
    numRegions int unsigned not null,	# number of regions in this contig (each region has different value for sequence-count and reads-count)
    regStart longblob not null,	# starting coordinates of significant regions in this contig (see example below)
    regLength longblob not null,	# length (in bases) of each significant regions sequence-count for each significant region
    seqCount longblob not null,	# sequence-count for each significant region
    regCount longblob not null,	# reads-count for each significant region
    sumCount int unsigned not null,	# Integrated reads-count sum (inner-product of columns 22 and 24)
              #Indices
    INDEX(chrom,chromStart)
);
