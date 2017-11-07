# Sentimental Analysis using Naive Bayes Classifier
## Getting Started
1. `Train.java` is the java program used to train the Naive Bayes Classifier.
2. `Test.java` tests `precision`, `recall` and `F1` score for each class and outputs the results.
3. In either case, you can set the values of `binNB` for Binary Naive Bayes and `checkStop` to include or exclude stop words by setting them as either `true` or `false`.
## Members
|Name|ID No|
|:--:|:---:|
|B V Krishna Bharadwaj|2015A7PS0076H|
|M Anurag|2015A7PS0074H|
|P V Nikhilanj|2015AAPS0190H|
## Results
|Values|Basic NB|Only Binary NB|Only Stop words|Both Binary NB and Stop words
|:--:|:---:|:---:|:---:|:---:|
|+ Precision|0.517830|0.517224|0.508999|0.509001|
|+ Recall|0.968880|0.970560|0.984160|0.983920|
|+ F1|0.674933|0.674825|0.670975|0.670922|
|- Precision|0.482170|0.482776|0.491001|0.490999|
|- Recall|0.902160|0.905920|0.949360|0.949120|
|- F1|0.628455|0.629881|0.647250|0.647192|
## Observations
* All the values have been checked twice.
* There is no significant increase or decrease in values by considering either binary naive bayes or stopwords. In practice, we need not check for these.