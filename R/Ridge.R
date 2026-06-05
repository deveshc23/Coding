library(readr)
library(dplyr)
library(stringr)
library(Matrix)
library(glmnet)
library(caret)  # For confusionMatrix

# Load and preprocess
df <- read_csv("amazon_reviews.csv") %>%
  select(overall, reviewText) %>%
  filter(!is.na(overall), !is.na(reviewText))

preprocess <- function(text) {
  text <- tolower(text)
  text <- str_replace_all(text, "[[:punct:]]", " ")
  words <- unlist(str_split(text, "\\s+"))
  words <- words[words != ""]
  return(words)
}

processed_reviews <- lapply(df$reviewText, preprocess)
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

# Keep top 500 words by frequency
word_freq <- colSums(bow_df)
top_words <- names(sort(word_freq, decreasing = TRUE))[1:500]
model_df <- model_df[, c("Rating", top_words)]

# Train-test split 80/20
set.seed(42)
n <- nrow(model_df)
train_idx <- sample(seq_len(n), size = 0.9 * n)
train_df <- model_df[train_idx, ]
test_df <- model_df[-train_idx, ]

# Prepare data for glmnet
x_train <- as.matrix(train_df[, -1])
y_train <- train_df$Rating

x_test <- as.matrix(test_df[, -1])
y_test <- test_df$Rating

# Fit ridge regression (alpha = 0)
cv_fit <- cv.glmnet(x_train, y_train, alpha = 0, nfolds = 30)
best_lambda <- cv_fit$lambda.1se 
cat("Best lambda chosen by CV:", best_lambda, "\n")

# Predict continuous ratings
preds_cont <- predict(cv_fit, newx = x_test, s = best_lambda)

# Apply inverse logit (sigmoid), then scale to [1,5]
inv_logit <- function(x) 1 / (1 + exp(-x))
preds_scaled <- 1 + 4 * inv_logit(preds_cont)

# Round to nearest valid rating
preds_final <- pmin(pmax(round(preds_scaled), 1), 5)

# Evaluate accuracy
accuracy <- mean(preds_final == y_test)
cat("Test Accuracy (inv_logit scaled & rounded):", round(accuracy, 3), "\n")

# Confusion matrix
conf_mat <- confusionMatrix(
  factor(preds_final, levels = 1:5),
  factor(y_test, levels = 1:5)
)
print(conf_mat)

