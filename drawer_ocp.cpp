
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> combinations;
        generateAll(new char[2*n], 0, combinations, 2*n);
        return combinations;
    }
    
    void generateAll(char* current, int pos, vector<string> &combinations, int sizeRes)
    {

        if(sizeRes == pos)
        {
            if(valid(current, sizeRes))
            {               
                combinations.push_back(current);
            }          
            
        }
        else
        {
            current[pos] = '(';
            generateAll(current, pos+1, combinations, sizeRes);
            current[pos] = ')';
            generateAll(current, pos+1, combinations, sizeRes);
        }
    }
    bool valid(char* current, int sizeRes)
    {
        int balance = 0;
        for(unsigned int i = 0; i < strlen(current); i++)
        {
            if(current[i] == '(') balance++;
            else balance--;
            if(balance < 0) return false;
        }
        return (balance==0);   
    }
};
