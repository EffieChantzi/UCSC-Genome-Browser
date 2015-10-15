"access      Controls who can access file\n",
"accession   A unique, license-plate-like identifier for a file \n",
"age        Age of organism when sample taken, since fertilization or birth depending on life_stage\n",
"age_unit   Unit that age is expressed in. Can be second, minute, hour, day, week, month, year, or single letter abbreviations of the same\n",
"assay      One of the genomics assays\n",
"at_ratio  Ratio of A and T to total sequence (including Ns)\n",
"biosample_date  Date that biosample was obtained from donor\n",
"body_part Free text description of part of body sample is taken from\n",
"cdw_file_name  File name in big data warehouse relative to cdw root dir\n",
"cell_count  1 for single cell biosamples, otherwise estimated cell count to one significant digit is fine\n",
"cell_line    Name of cell line if any before differentiation protocols\n",
"chrom  If the file just refers to a single chromosome, that chromosome name is here\n",
"consent  Consent form donor agreed to.\n",
"data_set_id   Id that groups together a set of data under the same title\n",
"donor   Disidentified cell donor ID\n",
"enriched_in  Genomic regions where the expectation is the data will be concentrated as defined in the enrichment table\n",
"enrichment_chrM   How deeply the Mitochondria is covered compared to the genome as a whole\n",
"enrichment_chrX  Ratio of coverage on X chromosome vs. genome as a whole\n",
"enrichment_chrY  Ratio of coverage on Y chromosome vs. genome as a whole\n",
"enrichment_coding  Ratio of coverage of coding exons vs. the genome as a whole.\n",
"enrichment_common_snp   Ratio of coverage on commonly occurring (>1% of population) SNP loci to genome as a whole\n",
"enrichment_exon  Ratio of coverage of exons (including noncoding and UTR) to coverage of genome as a whole\n",
"enrichment_intron   Ratio of coverage of introns to coverage of benome as a whole.\n",
"enrichment_open Enrichment ratio on open chromatin as defined by a union of ENCODE DNase hypersensitivity data sets\n",
"enrichment_promoter  Enrichment ration on promoters defined as from -100 to +50 bases relative to transcription start site\n",
"enrichment_utr   Ratio of coverage of untranslated regions vs. genome as a whole\n",
"enrichment_utr3   Ratio of coverage of 3'UTR (after coding) vs. genome as a whole\n",
"enrichment_utr5   Ratio of coverage of 5'UTR (before coding) vs. genome as a whole\n",
"fastq_qual_mean   Mean quality scored as 10*-log10(errorProbability) or close to it.  >25 is good\n",
"fastq_qual_type   For fastq files either 'sanger' or 'illumina'\n",
"file_id  Numerical identifier for file,  generally you'll use accession instead\n",
"file_name  Name of file including extensions but without directory.  Based on accession\n",
"file_part  For files that are broken into multiple parts such at the 11M reads fastq from Illumina, which part (starting with 1) this is\n",
"file_size   Size of file in bytes \n",
"format  One of the file formats supported by the system or \"unknown\"\n",
"item_count   # of items in file: reads for fastqs, lines for beds, bases w/data for wig\n",
"keywords  words used to mark and find data set\n",
"lab  account name of submitting lab or other group\n",
"life_stage  Life stage of donor, either 'embryo' or 'postpartum'\n",
"map_ratio   Proportion of items that map to genome\n",
"map_target_base_count   Count of bases in mapping target - around 3 billion for a mammalian genome\n",
"map_target_seq_count   Number of chromosomes or other distinct sequences in mapping target\n",
"map_to_ecoli   The ratio of reads that map to E. coli\n",
"map_to_fly    The ratio of reads that map to  Drosophila melanogaster\n",
"map_to_human   The ratio of reads that map to Homo sapiens (when sequence is not supposed to be human)\n",
"map_to_mouse   The ratio of reads that map to Mus musculus (when sequence is not supposed to be mouse)\n",
"map_to_rat    The ratio of reads that map to Rattus norvegicus\n",
"map_to_repeat   The ratio of reads that map to the RepeatMasker library for the organism\n",
"map_to_ribosome   The ratio of reads that map to the ribosome\n",
"map_to_worm   The ratio of reads that map to C. elegant\n",
"map_to_yeast   The ratio of reads that map to Saccharomyces cerevisiae\n",
"md5    MD5 sum of file\n",
"meta   Used in tab-separated metadata files to connect to additional metadata in a tagStorm file\n",
"output  For pipelines with multiple outputs, this says which of the outputs in the pipeline protocol file this is\n",
"paired_end   the paired_end tag from the manifest.  Values 1,2 or ''\n",
"paired_end_concordance  % of uniquely aligning reads where pairs map close to each other and point right way\n",
"paired_end_distance_max Maximum distance between paired reads\n",
"paired_end_distance_mean  Average distance between paired reads\n",
"paired_end_distance_min   Minimum distance between paired reads\n",
"paired_end_distance_std   Standard deviation of distance between paired reads\n",
"paired_end_mate   Accession of file containing the read pair mates of the reads in this file\n",
"paired_end_reads    For paired end fastq files put '1' for first read, '2' for second\n",
"pipeline    Protocol file describing pipeline that leads to this file\n",
"pmid   pubmed ID of publication associated with this data set, may be a list\n",
"read_size   Length of a read in file\n",
"replicate   For replicated experiments which one this is\n",
"seq_depth   How deep on average the genome is covered by items\n",
"seq_sample  Groups together sets of files from a logical sequencing run on a sample.  Used with file_part and paired_end tags\n",
"sequencer  Name of sequencing machine or service\n",
"sex    Sex of donor.  Either 'male' 'female' 'mixed' or 'unknown'\n",
"sorted_by_target   If set to 1, then file is sorted by chromosome and position within chromosome\n",
"species   Binomial scientific name of species sample taken from\n",
"strain    For nonhuman samples, strain within species.  Example 'C57BL/6'\n",
"submit_dir  directory (relative to system submission root) where submitted from\n",
"submit_file_name   File name in submit relative to submit dir\n",
"submitter   account name of person submitting data set\n",
"t        For time series experiments, measurement time\n",
"t_unit   Unit that t is expressed in. Can be second, minute, hour, day, week, month, year, or single letter abbreviations of the same\n",
"title  Brief description of purpose of experimental data set\n",
"u4m_unique_ratio  u4mUniqPos/u4mReadCount - measures library diversity\n",
"ucsc_db  UCSC assembly database identifier for reference genome used in mapping.  Either hg19, hg38, mm9, or mm10\n",
"vcf_common_snp_ratio   Proportion of data in file that overlaps common snps occuring in 1% or more of population\n",
"vcf_dp  The depth of sequencing in the bam or other alignment file used to produce this VCF.  Should be 30 or more\n",
"vcf_genotype_count   How many genotypes, that is different individuals, in a VCF file\n",
"vcf_pass_ratio   Proportion of VCF records that pass quality filter\n",
"vcf_snp_ratio    Proportion of VCF records that are single nucleotide subsitutions as opposed to larger changes or indels\n",
