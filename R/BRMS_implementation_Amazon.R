library(readr)
library(dplyr)
library(stringr)
library(brms)
library(tidyr)
library(Matrix)
library(caret)

df <- read_csv("amazon_reviews.csv") %>%
  select(overall, reviewText) %>%
  filter(!is.na(overall), !is.na(reviewText))

preprocess <- function(text) {
  text <- tolower(text)
  text <- str_replace_all(text, "[[:punct:]]", " ")
  words <- unlist(str_split(text, "\\s+"))
  words <- words[words != ""]  # Remove empty strings
  return(words)
}

processed_reviews <- lapply(df$reviewText, preprocess)
processed_reviews<-lapply(processed_reviews, unique)
vocab <- unique(unlist(processed_reviews))

rows <- rep(seq_along(processed_reviews), sapply(processed_reviews, length))
cols <- unlist(lapply(processed_reviews, function(words) match(words, vocab)))
valid <- !is.na(cols)
rows <- rows[valid]
cols <- cols[valid]


bow_sparse <- sparseMatrix(
  i = rows,
  j = cols,
  x = 1,
  dims = c(length(processed_reviews), length(vocab)),
  dimnames = list(NULL, vocab)
)

ratings <- df$overall
bow_df <- as.data.frame(as.matrix(bow_sparse))
colnames(bow_df) <- make.names(colnames(bow_df), unique = TRUE)
model_df <- cbind(Rating = ratings, bow_df)

# Keep top 500 most frequent words
word_freq <- colSums(bow_df)
top_words <- names(sort(word_freq, decreasing = TRUE))[1:500]
model_df <- model_df[, c("Rating", top_words)]

# Convert Rating to ordered factor
model_df$Rating <- factor(model_df$Rating, levels = 1:5, ordered = TRUE)

# Split into train and test sets
set.seed(42)
n <- nrow(model_df)
train_idx <- sample(seq_len(n), size = 0.8 * n)
train_df <- model_df[train_idx, ]
test_df  <- model_df[-train_idx, ]

# Define formula
formula <- as.formula(
  paste("Rating ~", paste(paste0("`", top_words, "`"), collapse = " + "))
)

# Fit ordinal regression model
fit <- brm(
  formula = formula,
  data = train_df,
  family = cumulative("logit"),
  chains = 4,
  iter = 1000,
  cores = 2,
  seed = 42
)

# Predict class probabilities
pred_probs <- posterior_epred(fit, newdata = test_df)  # dim: [samples, obs, categories]
pred_probs_mean <- apply(pred_probs, c(2, 3), mean)    # mean over samples

# Predicted class = argmax of probability
pred_classes <- apply(pred_probs_mean, 1, which.max)
true_classes <- as.integer(test_df$Rating)

# Evaluation
accuracy <- mean(pred_classes == true_classes)
cat("Test Accuracy:", round(accuracy, 3), "\n")

# Confusion matrix
conf_mat <- confusionMatrix(
  factor(pred_classes, levels = 1:5),
  factor(true_classes, levels = 1:5)
)
print(conf_mat)

# Optional plots
plot(fit)
pp_check(fit)
