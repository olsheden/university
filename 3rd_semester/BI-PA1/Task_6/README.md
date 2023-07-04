# Task description
    The challenge is to implement a programme that optimises supermarket shopping.

    Shopping in general and supermarket shopping in particular is a pleasure for some (shopaholia) and a black nightmare for others (shopaphobia). While shopaholics are happy to browse the shelves and see which goods are better or on sale (much to the delight of marketers), shopaphobics suffer at the thought of time wasted in this way. The maximum expected performance of a shopaphobic is to buy according to a pre-prepared list. This is where our program comes into play.

    Suppose we are given a shopping list. Our task is to buy the listed goods while spending as little time as possible in the supermarket. Most of the time is wasted searching for the specified goods. Shopaholics do not consider time when shopping, so they do not pay proper attention to the organization of the shopping list. In a linear traversal of such a list, we go back and forth through the supermarket, and the shopping has a time complexity of up to O( list_length * supermarket_size ). By rearranging the list appropriately, we can achieve time savings by traversing the supermarket only once, and reduce the time complexity to a painful but tolerable value of O( max(list_length, supermarket_size )). This will be the task of the implemented program.

    Assume that we know the distribution of goods on the shelves. For each shelf, we have specified individual goods (chains), each good is on a separate line. The shelves are entered in the input in the order 0, 1, 2, ..., this numbering is also the order in which we go through the supermarket.

    The input of shelves is followed by a blank line and then one or more shopping lists. If there are multiple shopping lists, they are separated by a blank line. The shopping lists contain the desired items, again each item on a separate line.

    The program loads the specified shelf layout and shopping list(s). For each shopping list, it then prints its optimized form:

    the goods on the shopping list are arranged so that they are on the shelves with increasing (more precisely: non-decreasing) numbers,
    if the goods are on the same shelf, the resulting relative order respects the order on the original list,
    if an item is available on more than one shelf, we take it from the first possible shelf,
    if the item is not available in the supermarket, we place it at the end of the list.
    Another minor problem is that shopping lists are not accurate. For example, there is a 'tomato' on the list, but in reality the store has 'red tomato', 'yellow tomato' and 'Cherry Tomatoes in Box'. Some people don't see the problem with this, as it is clear that "it takes YYY to make XXX." Our program will handle this similarly to the average intelligent AI: if we can't find an item with the same name, we take the item that contains the name of the desired item as a substring. Moreover (given the conditions above), this means the first matching good from the first possible shelf. We will not distinguish between upper and lower case when matching.

    The output of the program is a modified shopping list with the reordered item names. In addition, for each item the shelf number where the item is located and the name of the item as given by the supermarket will be displayed.

    The program must check the input data. If the input is invalid, the program must detect this, print an error message and exit. The following is considered an error:

    Missing shelf number when entering goods (shelf 0 must be the first line of the input),
    invalid entry of shelf number,
    shelf numbers do not form the sequence 0, 1, 2, ...,
    missing blank line after the end of the goods entry.
    A reasonably implemented naive algorithm is sufficient to handle the basic and optional tests. To get the bonus, we need to implement a more efficient algorithm that can handle long lists of items.