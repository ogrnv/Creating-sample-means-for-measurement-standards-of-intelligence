
According to https://en.wikipedia.org/wiki/Repeatability#Psychological_testing:

    When retested, testees may remember their answers, which could affect answers on the second administration.

The effect does not allow any static intelligence test to be a measurement standard of intelligence.
Even a single use of such a test is not reliable because it is not known whether a subject has taken the test in the past.
Two other reasons:
 - change in subject's intelligence over time and
 - training
also do not allow static IQ tests to become standards.

But a population of randomly generated tests is suitable to be a measurement standard of intelligence, provided that tests scores (from an AI or an intelligent being) are normally distributed with small standard deviations from the sample means(details below).

A description of the used standards of intelligence is FIRST-NB.html from https://github.com/ogrnv/random-intelligence-tests
Further, instead of the word "game", the words "round of test" will be used.  

This repository provides tools for creating the sample means: a "standard" and a "means" programs.
Both were developed with gcc version 12.2.0 Linux.

The "standard" program generates tests - samples of population of some complexity which is determined by 3, 4, 5, 6 arguments(see below). The program has a Monte Carlo solver (MCs) of the test tasks.
As result, the "standard" creates a file of 4-byte floating point values ​​- each of which is a number of moves made by the MCs in each round and prints one step means.
These means ​​are calculated as M/(rounds*stp);
where M is the number of moves made by MCs in a test;
rounds -  the number of rounds in one test;
stp - the number of steps in every round.
Another way to get the similar means is provided by "means" program.

The "standard" gets the seven arguments:
1) the number of tests (up to tmax #define tmax 5000);
2) the number of rounds in one test (up to rmax #define rmax 100000);
3) the number steps in one round;
4) the size of the side of a square board;
5) the number of types of chips are placed on the board;
6) the number of chips on the board;
7) 1 - print debug info on console, 0 - do not print.

The "means" gets the four arguments:
1) the number of tests, it can be different from the one given to "standard";
2) the number of rounds in one test, it can be different from the one given to "standard";
3) steps in one round, it should be the same as given to "standard";
4) the name of input file up to 300 chars.
The input file can be a file from the "standard" or a concatenation of several files obtained with the same 3, 4, 5, 6 arguments.
The "means" writes the means, similar to those printed by the "standard", - (4-bytes floating point values) in an output file.

Having the means of the tests it is possible to get statistical properties of distribution of the means.
The intelligence score from the test results can be calculated as 1000/mean

R examples:

> con=file("means_2000t_1040r_2s_2-8x8-2-42", "rb");
v<-c(readBin(con,"double",2000,size=4))
ks.test (v, 'pnorm', mean=mean(v), sd=sd(v))
shapiro.test (v)
par(mfrow=c(1,1))
d <- density(v)
plot(d)
rez <- t.test(v, conf.level=0.9999)
ci <- rez$conf.int
ci[1]
ci[2]
ci[2]/ci[1]

	Asymptotic one-sample Kolmogorov-Smirnov test

data:  v
D = 0.010407, p-value = 0.9819
alternative hypothesis: two-sided

Warning message:
In ks.test.default(v, "pnorm", mean = mean(v), sd = sd(v)) :
  ties should not be present for the Kolmogorov-Smirnov test

	Shapiro-Wilk normality test

data:  v
W = 0.99946, p-value = 0.8704

[1] 23.79008
[1] 23.89
[1] 1.0042
> 
-----
> con=file("means_2000t_240r_2s_2-8x8-3-42_480000", "rb");
v<-c(readBin(con,"double",2000,size=4))
ks.test (v, 'pnorm', mean=mean(v), sd=sd(v))
shapiro.test (v)
par(mfrow=c(1,1))
d <- density(v)
plot(d)
rez <- t.test(v, conf.level=0.9999)
ci <- rez$conf.int
ci[1]
ci[2]
ci[2]/ci[1]

	Asymptotic one-sample Kolmogorov-Smirnov test

data:  v
D = 0.0096145, p-value = 0.9926
alternative hypothesis: two-sided

Warning message:
In ks.test.default(v, "pnorm", mean = mean(v), sd = sd(v)) :
  ties should not be present for the Kolmogorov-Smirnov test

	Shapiro-Wilk normality test

data:  v
W = 0.99953, p-value = 0.9346

[1] 126.4101
[1] 127.5327
[1] 1.008881
> 
#./standard 100 5 12 8 7 42 0

v <- c(4223.916504,5661.783203,5439.416504,4936.649902,5443.466797,5397.766602,5364.183105,3820.866699,4797.083496,4663.883301,4159.916504,5305.616699,6212.950195,4534.266602,4779.183105,4503.466797,4823.350098,5171.433105,5948.316895,5323.516602,5450.033203,4355.700195,5970.649902,4445.866699,5157.649902,3686.333252,3449.383301,4662.333496,4358.816895,4143.100098,4543.833496,5497.350098,5561.250000,4594.183105,5762.033203,4420.166504,4958.083496,4912.116699,5587.133301,4700.200195,4004.266602,4140.200195,5648.000000,2997.083252,5720.600098,5176.450195,3743.966553,4572.883301,4840.950195,5715.950195,5551.850098,5352.549805,6006.966797,6834.416504,5079.166504,2967.983398,4253.399902,3855.783447,5192.600098,3456.733398,4688.433105,5691.399902,5489.783203,4660.333496,5686.483398,6169.183105,5028.649902,4766.799805,5103.916504,4131.950195,4162.549805,3370.983398,6045.383301,3868.149902,4936.299805,4314.316895,6143.000000,3652.149902,4017.666748,5077.316895,4284.000000,4226.783203,4866.016602,5831.833496,3852.366699,4860.083496,5286.333496,4011.483398,5146.799805,5138.850098,3575.216553,4428.100098,5797.649902,6686.633301,3621.166748,4683.966797,3759.866699,3633.983398,3778.016602,4406.100098)
> ks.test (v, 'pnorm', mean=mean(v), sd=sd(v))
shapiro.test (v)
par(mfrow=c(1,1))
d <- density(v)
plot(d)
rez <- t.test(v, conf.level=0.9999)
ci <- rez$conf.int
ci[1]
ci[2]
ci[2]/ci[1]

	Asymptotic one-sample Kolmogorov-Smirnov test

data:  v
D = 0.044146, p-value = 0.9899
alternative hypothesis: two-sided


	Shapiro-Wilk normality test

data:  v
W = 0.9918, p-value = 0.8067

[1] 4474.978
[1] 5139.403
[1] 1.148476
>
