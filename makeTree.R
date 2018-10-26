library(ggtree)
library(treeio)
library(ggplot2)
file <- "Documents/lineageTrack/test.txt"
nhx = read.nhx(file)
g = ggtree(nhx,ladderize = FALSE,aes(color=as.integer(DIV)*as.integer(OLD)),size=1) + theme_tree2() + geom_nodelab(size=2, color="blue4",hjust = 0) + scale_color_gradient2(low = "blue",high = "red") + theme(axis.text.x = element_text(angle = 90, hjust = 1))