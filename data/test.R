rm(list = ls())

library(jsonlite)
library(ggplot2)
data <- fromJSON("MCMC_param/save_MCMC0.json")

data0 = data$classe_0
num_data0 <- lapply(data0, as.numeric)  
num_data0$x0 = num_data0$x0[2]*17282163
df_temp0 <- as.data.frame(num_data0)
df0 =df_temp0


for (i in 1:99) {
  
  filename <- paste0("MCMC_param/save_MCMC", i, ".json")
  data <- fromJSON(filename)
  data0 = data$classe_0
  num_data0 <- lapply(data0, as.numeric)  
  num_data0$x0 = num_data0$x0[2]*17282163
  df_temp0 <- as.data.frame(num_data0)
  df0 = rbind(df0, df_temp0)

}

intervals0 <- apply(df0, 2, function(column) quantile(column, c(0.025, 0.975)))
intervals0




MCMC_data <- fromJSON("MCMC_result/data_MCMC0.json")
MCMC_data0 = MCMC_data$Classe1
num_MCMC_data0 <- lapply(MCMC_data0, as.numeric)  
df_temp0 <- as.data.frame(num_MCMC_data0)
dfMCMC0 =df_temp0

Classe1_list = list()
Classe1_list[[length(Classe1_list) + 1]] <- dfMCMC0
for (i in 1:99) {
  filename <- paste0("MCMC_result/data_MCMC", i, ".json")
  MCMC_data <- fromJSON(filename)
  MCMC_data0 = MCMC_data$Classe1
  num_MCMC_data0 <- lapply(MCMC_data0, as.numeric)  
  df_temp0 <- as.data.frame(num_MCMC_data0)
  dfMCMC0 =df_temp0
  Classe1_list[[length(Classe1_list) + 1]] <- dfMCMC0
}

### compartiement D ###
Compartiment = 5
df1 <- data.frame(matrix(ncol = 295, nrow = 100))
colnames(df1) <- paste0("Jour_", 1:295)

for (j in 1:295) {
  COMP1 = c()
  for (i in 1:100) {
    COMP1 = c(COMP1,Classe1_list[[i]][j,Compartiment])
  }
  df1[,j] = COMP1
}

df_result <- data.frame(matrix(ncol = 295, nrow = 100))
colnames(df_result) <- paste0("Jour_", 1:295)

df_result[,1] = df1[,1]
for(i in 2:295){
  df_result[,i] = df1[,i] - df1[,i-1] 
}


df_stat1 <- data.frame(median = numeric(295), lower = numeric(295), upper = numeric(295))
for (j in 1:295) {
  df_stat1$median[j] = median(df1[,j])
  df_stat1$lower[j] = quantile(df1[,j], c(0.025, 0.975))[1]
  df_stat1$upper[j] = quantile(df1[,j], c(0.025, 0.975))[2]
}

df_stat2 <- data.frame(median = numeric(295), lower = numeric(295), upper = numeric(295))
for (j in 1:295) {
  df_stat2$median[j] = median(df_result[,j])
  df_stat2$lower[j] = quantile(df_result[,j], c(0.025, 0.975))[1]
  df_stat2$upper[j] = quantile(df_result[,j], c(0.025, 0.975))[2]
}

days = 1:295
ggplot(df_stat1, aes(x=days)) +
  geom_line(aes(y=median), color="blue") +
  geom_ribbon(aes(ymin=lower, ymax=upper), fill="skyblue", alpha=0.4) +
  labs(title="Daily Simulations with 95% Credible Interval", y="Value") +
  theme_minimal()


death = read.table('day_data_csv.csv',header = TRUE, sep = ",")
ggplot(df_stat2, aes(x=days)) +
  geom_line(aes(y=median), color="blue") +
  geom_ribbon(aes(ymin=lower, ymax=upper), fill="skyblue", alpha=0.4) +
  geom_point(data=death, aes(y=death), color="black",shape=8) + 
  labs(title="Daily Simulations with 95% Credible Interval", y="Value") +
  theme_minimal()


### COMPARTIMENT Q ###
Compartiment = 4
df1 <- data.frame(matrix(ncol = 295, nrow = 100))
colnames(df1) <- paste0("Jour_", 1:295)

for (j in 1:295) {
  COMP1 = c()
  for (i in 1:100) {
    COMP1 = c(COMP1,Classe1_list[[i]][j,Compartiment])
  }
  df1[,j] = COMP1
}

df <- data.frame(matrix(ncol = 42, nrow = 100))
colnames(df1) <- paste0("Jour_", 1:42)
for(j in 0:41){
  somme <- data.frame(matrix(ncol = 1, nrow = 100))
  for(i in 1:7){
    somme[,1] = somme[,1] + df1[,j*7 + i] 
  }
  df[,j+1] = somme[,1] 
}

df_stat1 <- data.frame(median = numeric(42), lower = numeric(42), upper = numeric(42))
for (j in 1:42) {
  df_stat1$median[j] = median(df1[,j])
  df_stat1$lower[j] = quantile(df1[,j], c(0.025, 0.975))[1]
  df_stat1$upper[j] = quantile(df1[,j], c(0.025, 0.975))[2]
}


week_hosp= read.table('hosp_week_csv.csv',header = TRUE, sep = ",")
hosp= week_hosp[-45:-43,1]
week_hosp = data.frame(hosp)

weeks = 1:42
ggplot(df_stat1, aes(x=weeks)) +
  geom_line(aes(y=median), color="blue") +
  geom_ribbon(aes(ymin=lower, ymax=upper), fill="skyblue", alpha=0.4) +
  geom_point(data=week_hosp, aes(y=hosp), color="black",shape=8) + 
  labs(title="Daily Simulations with 95% Credible Interval", y="Value") +
  theme_minimal()

plot(weeks,week_hosp$hosp)




