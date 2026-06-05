n0<-0
k1<-0.1
k2<-1
t_max<-1000
n_sim<-10
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

plot(NULL, xlim = c(0, t_max), ylim = c(0, 25), 
     xlab = "Time", ylab = "Number of Molecules A(t)", 
     main = "Gillespie Algorithm: Multiple Simulations")
colors <- rainbow(n_sim)
t_grid <- seq(0, t_max, length.out = 2000)
all_paths <- matrix(NA, nrow = length(t_grid), ncol = n_sim)
for (i in 1:n_sim) {
  res <- run_gillespie(k1, k2, n0, t_max)
  lines(res$time, res$N, col = colors[i],type = "s")
  all_paths[, i] <- approx(res$time, res$N, xout = t_grid, method = "constant", rule = 2)$y
}

avg_line <- rowMeans(all_paths)
lines(t_grid, avg_line, lwd = 3, col = "black")

avg_after_100 <- avg_line[t_grid > 100]
std_dev <- sd(avg_after_100)
cat("Standard Deviation of the average line for t > 100:", std_dev, "\n")
