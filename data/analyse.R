data = read.csv('integration.txt',header = FALSE, sep = " ")
death = read.table('day_data.csv',header = FALSE, sep = ",")

data = data[,-296]
death = death[,-1]

data_new = data
for (i in 2:295) {
  data_new[5,i] = data[5,i] - data[5,i]
}




plot(x = 1:295, death[1,], xlim = c(1, 295), ylim=range(c(0,10000)))
par(new = TRUE)
plot(x = 1:295, data_new[5,], xlim = c(1, 295), ylim=range(c(0,10000)))

