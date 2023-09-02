load('social_contact_analysis.RData')
write.csv(location_matrices$total, "social_contact_matrix.csv", row.names=FALSE)
write.csv(location_matrices$home, "social_contact_matrix.csv", row.names=FALSE)
write.csv(location_matrices$work, "social_contact_matrix.csv", row.names=FALSE)
write.csv(location_matrices$school, "social_contact_matrix.csv", row.names=FALSE)
write.csv(location_matrices$transport, "social_contact_matrix.csv", row.names=FALSE)

write.csv(location_matrices$otherplace + location_matrices$leisure, "social_contact_matrix_loisir_autre.csv", row.names=FALSE)


rm(list = ls())

library(jsonlite)

data <- fromJSON("MCMC_param/save_MCMC0.json")

data0 = data$classe_0
data1 = data$classe_1

num_data0 <- lapply(data0, as.numeric)  
num_data1 <- lapply(data1, as.numeric) 

num_data0$x0 = num_data0$x0[2]*17282163
num_data1$x0 = num_data1$x0[2]*17282163

df_temp0 <- as.data.frame(num_data0)
df_temp1 <- as.data.frame(num_data1)

df0 =df_temp0
df1 = df_temp1

for (i in 1:999) {
  
  filename <- paste0("MCMC_param/save_MCMC", i, ".json")
  data <- fromJSON(filename)
  
  data0 = data$classe_0
  data1 = data$classe_1
  
  num_data0 <- lapply(data0, as.numeric)  
  num_data1 <- lapply(data1, as.numeric) 
  
  num_data0$x0 = num_data0$x0[2]*17282163
  num_data1$x0 = num_data1$x0[2]*17282163
  
  df_temp0 <- as.data.frame(num_data0)
  df_temp1 <- as.data.frame(num_data1)
  
  df0 = rbind(df0, df_temp0)
  df1 = rbind(df1, df_temp1)
}

intervals0 <- apply(df0, 2, function(column) quantile(column, c(0.025, 0.975)))
intervals1 <- apply(df1, 2, function(column) quantile(column, c(0.025, 0.975)))

intervals0
intervals1





data <- fromJSON("integration.json")
data0 = data$Classe1
data1 = data$Classe2

num_data0 <- lapply(data0, as.numeric)  
num_data1 <- lapply(data1, as.numeric) 

data_classe1 <- as.data.frame(num_data0)
data_classe2 <- as.data.frame(num_data1)
data_all <- data_classe1 + data_classe2


death = read.table('day_data.csv',header = FALSE, sep = ",")

month = read.table('death_month_age.csv',header = FALSE, sep = ",")
hosp = read.table('hosp_week_age2.csv',header = FALSE, sep = ",")
death = death[,-1]
month = month[,-1]
hosp = hosp[,-1]



#for (i in 2:295) {
#  data_new[5,i] = data[5,i] - data[5,i]
#}




plot(x = 1:295, death[1,], xlim = c(1, 295), ylim=range(c(0,10000)))
par(new = TRUE)

plot(x = 1:295, data_all$D, xlim = c(1, 295), ylim=range(c(0,10000)))


plot(x = 237:295, death[2,237:295], xlim = c(237, 295), ylim=range(c(0,2000)))
par(new = TRUE)

plot(x = 1:295, data_all$Q, xlim = c(237, 295), ylim=range(c(0,2000)))



hosp1=NULL
for (i in seq(1, 295, by=7)) {
  hosp1 = c(hosp1,data_classe1$Q[i])
}

plot(x = 1:42, hosp[1,], xlim = c(1, 42), ylim=range(c(0,10000)))
par(new = TRUE)

plot(x = 1:43, hosp1, xlim = c(1, 43), ylim=range(c(0,10000)))



MCMC_data <- fromJSON("MCMC_result/data_MCMC0.json")

MCMC_data0 = MCMC_data$Classe0
MCMC_data1 = MCMC_data$Classe1

num_MCMC_data0 <- lapply(MCMC_data0, as.numeric)  
num_MCMC_data1 <- lapply(MCMC_data1, as.numeric) 

df_temp0 <- as.data.frame(num_MCMC_data0)
df_temp1 <- as.data.frame(num_MCMC_data1)

dfMCMC0 =df_temp0
dfMCMC1 = df_temp1

for (i in 1:999) {
  
  filename <- paste0("MCMC_result/data_MCMC", i, ".json")
  data <- fromJSON(filename)
  
  data0 = data$classe_0
  data1 = data$classe_1
  
  num_data0 <- lapply(data0, as.numeric)  
  num_data1 <- lapply(data1, as.numeric) 
  
  num_data0$x0 = num_data0$x0[2]*17282163
  num_data1$x0 = num_data1$x0[2]*17282163
  
  df_temp0 <- as.data.frame(num_data0)
  df_temp1 <- as.data.frame(num_data1)
  
  df0 = rbind(df0, df_temp0)
  df1 = rbind(df1, df_temp1)
}




       