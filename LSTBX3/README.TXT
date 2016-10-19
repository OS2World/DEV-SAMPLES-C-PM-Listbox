August 8th, 1994

************************************************************************
* Notes of Interest                                                    *
************************************************************************
This source code illustrates one of the three major aspects of custom
control design and the ICLUI:
               1) Wrapper an existing PM (custom) control
               2) Wrapper a replacement PM custom control
               3) Write a custom control using the ICLUI nomeclature

If you haven't already guessed, we illustrate number 2.  The other 2 are
illustrated in the book, "OS/2 V2 C++ Class Library:  Power GUI Programming
with C Set++" (published by VNR), and the article, "Writing OS/2 PM Controls
in C++" (OS/2 Developer Sept/Oct '94) respectively.

We have compiled and tested the source code using IBM C Set++ Version 2.1,
at class library CSD level 6 (i.e. CTM0006).  If you have any questions or
comments, please direct them to us AND NOT IBM.  This class library is NOT
supported by IBM's C Set++ Group.

Please direct any comments, questions, and such to either Matt Smith
(Internet: prominar@io.org CompuServe: 70363,1175) or Mark Benge
(Internet: banzai@vnet.ibm.com CompuServe: 73532,2063  VNET: banzai AT CARVM3)

Mark Benge
Matt Smith

************************************************************************
* LMMs (i.e. Last Minute Modifications)                                *
************************************************************************
At press time, we made a minor modifcation in the source code which conflicts
with the following sentence in the section "One Size Fits All":  "We will use
the default for the minimum height".  Instead of using the ICLUI default
setting for the height (i.e. 100), we will use the "absolute" minimum height
which is the height required to display 1 item.  (See calcMinimumSize() for
more info).  It also give us the opportunity to exercise the LMX_CALCSIZE
api.  To illustrate the effect of calcMinimumSize(), comment out the following
line in ic.cpp:
                      IListBox::horizontalScroll |

Sorry for any inconvenience.
MS/MB
