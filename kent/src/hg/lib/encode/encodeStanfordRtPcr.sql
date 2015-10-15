# encodeStanfordRtPcr.sql was originally generated by the autoSql program, which also 
# generated encodeStanfordRtPcr.c and encodeStanfordRtPcr.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Stanford RTPCR in ENCODE Regions (BED5+)
CREATE TABLE encodeStanfordRtPcr (
    chrom varchar(255) not null,	# Chromosome or FPC contig
    chromStart int unsigned not null,	# Start position in chromosome
    chromEnd int unsigned not null,	# End position in chromosome
    name varchar(255) not null,	# Accession of gene (or unknown/negative)
    score int unsigned not null,	# Score from 0-1000
    primerPair varchar(255) not null,	# Long name of primer pair
    count int unsigned not null,	# Endogenous copies in cells
              #Indices
    INDEX (chrom(6),chromStart),
    INDEX (name(10))
);
