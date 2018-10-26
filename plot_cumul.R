test <- read_delim("~/Documents/lineageTrack/test.txt",
"\t", escape_double = FALSE, trim_ws = TRUE)
melt = melt(test,measure.vars = 'Births',id.vars = c('Lineage','Frame','Field','DistToEdge'))
melt$cumul = ave(melt$value, melt$Lineage, FUN=cumsum)
test$grp = paste(test$Field,test$Lineage)
melt = melt(test,measure.vars = 'Births',id.vars = c('grp','Frame','DistToEdge'))
melt$cumul = ave(melt$value, melt$grp, FUN=cumsum)
ggplot() + geom_step(data=melt,mapping=aes(x=Frame*4,y=cumul,group=factor(grp),color=factor(grp)),size=0.75) + theme_Publication() + scale_color_discrete(l = 50,h = c(230,310)) + guides(color=FALSE) + xlab("Time (min)")
ggplot() + geom_step(data=melt,mapping=aes(x=Frame*2,y=cumul,group=factor(DistToEdge),color=log(DistToEdge/10)),size=0.75) + theme_Publication(base_size = 17)+ xlab("Time (min)") + scale_colour_viridis_c() + xlim(100,200) + scale_x_continuous(breaks=c(200,225,250,275,300,325,350,375),labels = c("0","25","50","75","100","125","150","175"),limits = c(200,375)) + xlab("Time elapsed since adding ampicillin (min)") + ylab("Cumulative number of cells") + ggtitle("Lineages of cells alive upon adding the drug") + guides(color = guide_colorbar(barwidth = 10, barheight = 0.5),ticks=FALSE) + labs(color = "Log(distance to edge of colony [µm])") 