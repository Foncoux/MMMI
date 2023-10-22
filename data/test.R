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

for (i in 1:99) {
  
  filename <- paste0("MCMC_param/save_MCMC", i, ".json")
  data <- fromJSON(filename)
  
  data0 = data$classe_0
  #  data1 = data$classe_1
  
  num_data0 <- lapply(data0, as.numeric)  
  #  num_data1 <- lapply(data1, as.numeric) 
  
  num_data0$x0 = num_data0$x0[2]*17282163
  #  num_data1$x0 = num_data1$x0[2]*17282163
  
  df_temp0 <- as.data.frame(num_data0)
  #  df_temp1 <- as.data.frame(num_data1)
  
  df0 = rbind(df0, df_temp0)
  #  df1 = rbind(df1, df_temp1)
}

intervals0 <- apply(df0, 2, function(column) quantile(column, c(0.025, 0.975)))
intervals1 <- apply(df1, 2, function(column) quantile(column, c(0.025, 0.975)))

intervals0
intervals1



MCMC_data <- fromJSON("MCMC_result/data_MCMC0.json")

MCMC_data0 = MCMC_data$Classe1
#MCMC_data1 = MCMC_data$Classe2

num_MCMC_data0 <- lapply(MCMC_data0, as.numeric)  
#num_MCMC_data1 <- lapply(MCMC_data1, as.numeric) 

df_temp0 <- as.data.frame(num_MCMC_data0)
#df_temp1 <- as.data.frame(num_MCMC_data1)

dfMCMC0 =df_temp0
#dfMCMC1 = df_temp1

Classe1_list = list()
Classe1_list[[length(Classe1_list) + 1]] <- dfMCMC0
#Classe2_list = list()
#Classe2_list[[length(Classe2_list) + 1]] <- dfMCMC1

for (i in 1:99) {
  filename <- paste0("MCMC_result/data_MCMC", i, ".json")
  MCMC_data <- fromJSON(filename)
  
  MCMC_data0 = MCMC_data$Classe1
#  MCMC_data1 = MCMC_data$Classe2
  
  num_MCMC_data0 <- lapply(MCMC_data0, as.numeric)  
#  num_MCMC_data1 <- lapply(MCMC_data1, as.numeric) 
  
  df_temp0 <- as.data.frame(num_MCMC_data0)
#  df_temp1 <- as.data.frame(num_MCMC_data1)
  
  dfMCMC0 =df_temp0
#  dfMCMC1 = df_temp1
  
  Classe1_list[[length(Classe1_list) + 1]] <- dfMCMC0
#  Classe2_list[[length(Classe2_list) + 1]] <- dfMCMC1
}

Compartiment = 5

df1 <- data.frame(matrix(ncol = 295, nrow = 1000))
colnames(df1) <- paste0("Jour_", 1:295)
#df2 <- data.frame(matrix(ncol = 295, nrow = 1000))
#colnames(df2) <- paste0("Jour_", 1:295)
for (j in 1:295) {
  COMP1 = c()
  #COMP2 = c()
  for (i in 1:100) {
    COMP1 = c(COMP1,Classe1_list[[i]][j,Compartiment])
   # COMP2 = c(COMP2,Classe2_list[[i]][j,Compartiment])
    
    
  }
  df1[,j] = COMP1
  #df2[,j] = COMP2  
}
df_all = df1 + df2

df_stat1 <- data.frame(median = numeric(295), lower = numeric(295), upper = numeric(295))
for (j in 1:295) {
  df_stat1$median[j] = median(df1[,j])
  df_stat1$lower[j] = quantile(df1[,j], c(0.05, 0.95))[1]
  df_stat1$upper[j] = quantile(df1[,j], c(0.05, 0.95))[2]
}
df_stat2 <- data.frame(median = numeric(295), lower = numeric(295), upper = numeric(295))
for (j in 1:295) {
  df_stat2$median[j] = median(df2[,j])
  df_stat2$lower[j] = quantile(df2[,j], c(0.05, 0.95))[1]
  df_stat2$upper[j] = quantile(df2[,j], c(0.05, 0.95))[2]
}
df_stat_all <- data.frame(median = numeric(295), lower = numeric(295), upper = numeric(295))
for (j in 1:295) {
  df_stat_all$median[j] = median(df_all[,j])
  df_stat_all$lower[j] = quantile(df_all[,j], c(0.05, 0.95))[1]
  df_stat_all$upper[j] = quantile(df_all[,j], c(0.05, 0.95))[2]
}



library(ggplot2)
days = 1:295
death[1,]

ggplot(df_stat1, aes(x=days)) +
  geom_line(aes(y=median), color="blue") +
  geom_ribbon(aes(ymin=lower, ymax=upper), fill="skyblue", alpha=0.4) +
  labs(title="Daily Simulations with 95% Credible Interval", y="Value") +
  theme_minimal()

ggplot(death[1,], aes(x=days)) +
  geom_line(aes(y=median), color="blue") +
  geom_ribbon(aes(ymin=lower, ymax=upper), fill="skyblue", alpha=0.4) +
  labs(title="Daily Simulations with 95% Credible Interval", y="Value") +
  theme_minimal()





ggplot(df_stat2, aes(x=days)) +
  geom_line(aes(y=median), color="blue") +
  geom_ribbon(aes(ymin=lower, ymax=upper), fill="skyblue", alpha=0.4) +
  labs(title="Daily Simulations with 95% Credible Interval", y="Value") +
  theme_minimal()

vec = death[1,]
vec = as.vector(unlist(vec))
df_death <- data.frame(vec)
ggplot(df_stat_all, aes(x=days)) +
  geom_line(aes(y=median), color="blue") +
  geom_ribbon(aes(ymin=lower, ymax=upper), fill="skyblue", alpha=0.4) +
  geom_line(data=df_death, aes(x=days, y=vec), color="red")+
  labs(title="Daily Simulations with 95% Credible Interval", y="Value") +
  theme_minimal()

