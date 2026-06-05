n0<-0
k1<-0.1
k2<-1
t_max<-100000
run_gillespie<-function(k1,k2,n0,t_max){
  t<-0
  n<-n0
  time<-c(t)
  n_path<-c(n)
  while(t<t_max){
    r1<-runif(1,0,1)
    r2<-runif(1,0,1)
    alpha<-n*k1+k2
    if(alpha==0) break
    tau<-(1/alpha)*log(1/r1)
    t<-t+tau
    if(r2<k2/alpha){
      n<-n+1
    }
    else{
      n<-n-1
    }
    time<-c(time,t)
    n_path<-c(n_path,n)
  }
  return(data.frame(time=time,N=n_path))
}

res <- run_gillespie(k1, k2, n0, t_max)
sample_times <- seq(500, t_max, by = 1)
sampled_values <- approx(res$time, res$N, xout = sample_times, 
                         method = "constant", rule = 2)$y
hist(sampled_values, 
     breaks = seq(min(sampled_values)-0.5, max(sampled_values)+0.5, by = 1),
     col = "skyblue", 
     prob = TRUE,
     main = "Stationary Distribution of A(t)",
     xlab = "Number of Molecules",
     ylab = "Density")

theo_stat<-function(k1,k2,n){
  return((k2/k1)^n*exp(-(k2/k1))/factorial(n))
}
n_range <- 0:25
val <- sapply(n_range, function(n) theo_stat(k1, k2, n))
lines(n_range, val, type = "b", col = "red", lwd = 2, pch = 16)
legend("topright", legend = c("Simulated", "Theoretical"),
       col = c("skyblue", "red"), lwd = 2, bty = "n")
