# cnpLocke.sql was originally generated by the autoSql program, which also 
# generated cnpLocke.c and cnpLocke.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#CNP data from Locke
CREATE TABLE cnpLocke (
    chrom varchar(255) not null,	# Reference sequence chromosome or scaffold
    chromStart int unsigned not null,	# Start position in chrom
    chromEnd int unsigned not null,	# End position in chrom
    name varchar(255) not null,		# BAC Name
    variationType varchar(255) not null	# {Gain},{Loss},{Gain and Loss}
);
