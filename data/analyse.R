data = read.csv('integration.txt',header = FALSE, sep = " ")
death = read.csv('Death_1mars_to_14dec.csv',header = TRUE, sep = " ")

data = data[,-290]

plot(x = 1:289,death$x)
par(new=TRUE)
plot(x=1:289,data[5,])
