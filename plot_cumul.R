test <- read_delim("~/Documents/lineageTrack/test.txt",
"\t", escape_double = FALSE, trim_ws = TRUE)
View(test)
melt = melt(test,measure.vars = 'Births',id.vars = c('Lineage','Frame','Field'))
melt$cumul = ave(melt$value, melt$Lineage, FUN=cumsum)
test$grp = paste(test$Field,test$Lineage)
melt = melt(test,measure.vars = 'Births',id.vars = c('grp','Frame'))
melt$cumul = ave(melt$value, melt$grp, FUN=cumsum)
ggplot() + geom_step(data=melt,mapping=aes(x=Frame*4,y=cumul,group=factor(grp),color=factor(grp)),size=0.75) + theme_Publication() + scale_color_discrete(l = 50,h = c(230,310)) + guides(color=FALSE) + xlab("Time (min)")