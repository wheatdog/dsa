int HashCode(string s)
{
    int CharTable[26] = {17, 17,  4,  1,  2, 17, 15, 16, 15, 0,
                         17, 17,  5, 16, 10,  0,  0, 15,  5, 8,
                         12, 15, 15,  0,  0,  0};
    return CharTable[(s.front() - 'a')] + CharTable[(s.back() - 'a')] + 
        s.length() - 8;
}


