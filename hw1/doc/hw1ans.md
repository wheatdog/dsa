
<!--
TODO: 1.1(1), 1.4(4), 1.5(*), 1.6(*), 1.7(*) 
-->

\renewcommand{\questiontype}{Whatever You Want}

##

Professor Donald Knuth has been called "father of analysis of algorithms". He is also the
creator of TeX computer typesetting system. He found the galley proof of his great book,
The Art of Computer Programming, awful. Meanwhile, he saw for the first time the output
of high-quality digital typesetting system, and decided to design his own typesetting system,
TeX, to solve this problem. He used to pay $2.56 to those who find mistakes in his books
because "256 pennies is one hexadecimal dollar".



##
    
Claim: At the end of while loop, string array whose length is k return i = k.

1.  If string array's length is 0, i will not go into the while loop because
    i initialize to 0 and str\[i\]\(now is str\[0\]\) is already the end of the string.
    This algorithm then return i = 0, which is the length of the string.
2.  Assume Claim is correct at the case that string's length is $M$. We denote this string A.  
    When string's length is M + 1 (We denote this string B), $i$ comes to M which is
    A's end. However, str\[M\] isn't the end of B. Therefore, $i$ becomes to $M + 1$, and
    now str\[M + 1\] is the end of B. Finally, this algorithm return $i = M + 1$ when 
    the length of string is M + 1.

By 1, 2, and induction. We conclude this claim is correct when length of string 
is N, which N belong to {0} and N.

#

##

Without loss of generality, let a $\geq$ b. We know that any number bigger than n cannot
divide n without a remainder. Therefore, by definition, 1 $\leq$ gcd(a, b) $\leq$ min(a, b).
Since we choose i from min(a, b) to 1, the first i satisfing the if statement will be
the largest one which can divide a and b without remainder. This shows that i is gcd(a, b).


##

This value is 1, a = b $\times$ k, k > 1, k $\in$ N.

#

##

    a = l*k => k = a/l  
    b = l*j => j = b/l.  
    By definition, k = gcd(k, j)*r, j = gcd(k, j)*w, which gcd(r, w) = 1.  
    => a = l*gcd(a/l, b/l)*r, b = l*gcd(a/l, b/l)*w.  
    Claim: gcd(a, b) = l*gcd(a/l, b/l).  

1.  We can easily observe that a mod (l*gcd(a/l, b/l)) = 0 and b mod (l*gcd(a/l, b/l)) = 0\
2.  Suppose gcd(a, b) is greater than (l*gcd(a/l, b/l)) and denote it to (l*gcd(a/l, b/l)\*c) which c >= 2.  

    => a = l*gcd(a/l, b/l)\*r = l\*gcd(a/l, b/l)\*c\*A   
    b = l\*gcd(a/l, b/l)\*w = l\*gcd(a/l, b/l)\*c\*B  
    => r = c\*A  
    w = c\*B  
    => gcd(r, w) >= c >= 2. This is a contradiction. Therefore, gcd(a, b) = l*gcd(a/l, b/l).  

##

This value is 1, If the pseudo code enter that line, this means that the number from min(a, b) to 
2 couldn't divide a, b without remainder. By 1.2(1), we know that 1 <= gcd(a, b) <= min(a, b). 
Therefore 1 is the only value can return.

##

This value must be 2. If we choose 1, the if statement will always be true, this means that we 
will always return 1 * gcd(a, b) and never compute the answer. If we choose the number greater 
than 2, we will miss if a mod 2 = 0 and b mod 2 = 0 because for loop start from the number greater
than 2.

#

##
    
    n = 14     m = 56     ans =  1
    ------------------------------
    n =  7     m = 21     ans =  2

    n =  7     m = 14     ans =  2

    n =  7     m =  0     ans =  2
    ------------------------------
    n =  7     m =  0     ans = 14 

##

Claim: m will finally become 0.
1.  At the end of each iteration, m is getting smaller and smaller.  
    Case 1: if n \> m, n will swap with m. Therefore m becomes smaller.  
    Case 2: if n = m, m will become 0. m becomes smaller and is 0.  
    Case 3: if n < m, m will become (m-n). m becomes smaller.
2.  n will never become to 0.

3.  If we enter the line "m <- (m - n)", m >= n. m - n >= 0, this shows that m will getting
    smaller but still greater than 0. We notice that m will not have a chance to become 0
    before enter this statement, this means that m >= n > 0.  
    Case 1: if n = m != 1, m will become 0.  
    Case 2: Since m is getting smaller, m will finally become 1. m>=n>0, n will become 1, too. 
    m = m - n = 0.


##

    By definition, a = gcd(a, b)*k, b = gcd(a, b)*r. gcd(k, r) = 1,  k > r >= 1  
    => a - b = gcd(a, b)*(k - r).
    Case 1: r = 1
        a - b = gcd(a, b)*(k - 1). gcd(a - b, b) = gcd(a, b)*gcd(k-1, 1) = gcd(a, b), by 1.3(1).
    Case 2: r > 1
        a - b = gcd(a, b)*(k - r). gcd(a - b, b) = gcd(a, b)*gcd(k-r, r)
        if gcd(k-r, r) = c >= 2. k - r = c*A, r = c*B.
        => k = c*(A+B), r = c*B.
        => gcd(k, r) >= c >= 2.  This is a contradiction. Therefore, gcd(k-r, r) = 1.
        => gcd(a-b, b) = gcd(a, b).

##

None


          
#

##

    m = 56     n = 14     tmp =  *

    m = 56     n = 14     tmp =  *

##

    Claim1: 3a % 3b = 0 if a % b = 0.  
    a % b =0 => a = b * r.  0 < r
    => 3a = 3b * r   
    => 3a % 3b = 0  

    Claim2: 3a % 3b = 3k if a % b = k.
    a % b = k => a = b * r + k, 0 < k < b 
    => 3a = 3b * r + 3k, 0 < 3k < 3b
    => 3a % 3b = 3k

    In while loop, we check m % n == 0. 
    Case 1: m % n = 0, by Claim1, we know that 3m % 3n = 0, which will be out of while loop.
    Case 2: m % n = k != 0, m will become n, and n will become k. By Claim2, we know that 
            3m % 3n = 3k, 
            then 3m will become 3n, and 3n will become 3k.

    This imply that gcd-by-euclid(3a, 3b) and gcd-by-euclid(a, b) take the same iterations.


##



#

##

Code done

##

    AveRS: 11254
    AveF: 6491
    AveFF: 6491
    AveB: 18
    AveE: 8
