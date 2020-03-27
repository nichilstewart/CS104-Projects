CSCI 104 HW6: Tree Analysis

Name: Nichil Stewart

Email Address: nichilst@usc.edu


## Analysis Report:

1. "Which sizes of input cases did you test your program on? This would apply 
   both to the length m of the strings in the file, and the number n of 
   strings/queries."

   I first ran single sample tests on a dictionary .txt file borrowed from
   HW5, which had 1,000,000 strings ranging from 2 to ~20 characters.

   I later adjusted my program to run 1,000 iterative tests for a consistent
   time, and I used only the first 1000-2000 strings of the same character
   length. I also got a .txt file containing a number of longer web urls that
   went up to around ~100 characters in length, with around 1200 urls in total.


2. "For each of the two data structures, report how long each of your input 
   cases took. How long did it take per operation? Did it depend on the 
   parameters, and if so how? How did that depend on the parameters?"

   Over 3 samples with 1000 insertions, I had:
      AVL times: 0.00329268, 0.00483524, and 0.00244126 seconds
      Splay times: 0.00151165, 0.00420518, and 0.00258483 seconds
      Splay expensives: 366, 334, 21
    
   Per operation you can divide the total time by 1000, giving you times of:
      AVL times: 0.000003293, 0.000004835, 0.000002431, 0.000002441 seconds
      Splay times: 0.000001512, 0.000004205, 0.000002579, 0.000002585 seconds

   Samples with larger keys (the url set) took longer than those with shorter
   keys.

   Samples testing with greater total strings (over 1000) had larger times than
   samples with 1000 or fewer strings.

   Greater splay expensives seemed to improve the Splay time relative to AVL
   time when considered against samples with fewer expensive insertions. This
   can be seen in the first two samples with higher expensives relative to the
   last sample with fewer expensives. 


3. "Explain why you think the results turned out the way they did."

   Samples with larger keys take longer to fully compare, and thus took longer
   on average than samples with shorter keys. 

   Samples with more total strings have more total comparisons, and thus take
   longer to compare as well. 

   Samples with greater splay expensives indicate the tree needs re-balancing, 
   meaning the AVL program will need to do more rotations, and thus took longer
   on average than the Splay tree which did not need to do the same rebalacing.


4. "How do you think the running time would compare if you were to implement
   and analyze the following data structures? Briefly justify each, although
   you do not need to quantify how much slower/faster with any specificity."

   A. Unsorted List: Inserting into an unsorted list will run in O(1) constant 
      time, as you don't need to maintain any order. This will run very fast, 
      certainly faster than both AVL insert and Splay insert as each operation
      takes a single action.

   B. Sorted list: You would have to find the correct place to insert the item
      and move all the incorrectly placed nodes forward, thus it would run in
      O(n) time. This liley takes longer than both AVL insert and Splay insert,
      unless all the nodes are sorted smallest-to-largest before insertion. 

   C. Binary search tree, non-rotating variety: This would run essentially the
      same as AVL insert or Splay insert except the height of the tree will
      never be changed via internal rotations. It is almost certainly longer
      than both AVL insert and Splay insert in cases where a poorly balanced
      tree can force up to potentially n-comparisons for each node.

   D. Hash Table, with universal hash function: Hashtables insert function runs
      in amortized O(1) constant time, so it almost certainly runs faster in
      cases where the inserted nodes do not exceed the capacity of the hash
      function or it can account for a node total beyond the load balance.