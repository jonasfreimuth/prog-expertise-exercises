if (!require("randomNames", quietly = TRUE)) {
  cat("Package randomNames",
      "(https://cran.r-project.org/web/packages/randomNames/randomNames.pdf)",
      "not installed. ")
  installl <- askYesNo("Install now? (Uses default install.package parameters)")
  
  if (install) {
    install.packages("randomNames")
  } else {
    stop("Then no random names for you, sorry.")
  }
}

names <- strsplit(randomNames(n = 400, name.order = "first.last"), ", ")
names <- do.call(rbind, names)
names <- data.frame(first_names = names[, 1], last_names = names[, 2])

marks <- round(rnorm(n = nrow(names), mean = 3.5), 2)

while (any(marks < 1 | marks > 6)) {
  ind_out <- which(marks < 1 | marks > 6)
  marks[ind_out] <- round(rnorm(n = length(ind_out), mean = 3.5), 2)
}

names$marks <- as.character(marks)

write.table(names, "marks.tab", row.names = FALSE)

