#include<iostream>
#include <string>

using namespace std;

class TextEditor {
public:
    TextEditor()
    { ans="^";
    }

    void addText(string text) {
        if (ans == "^") {
            ans = text+"^";
        } else {
            int pos=findCursor();
            ans=ans.erase(pos,1);

            ans=ans.substr(0,pos)+text+"^"+ans.substr(pos);
        }
    }

    void backspace() {

            ans.erase(findCursor()-1,1);

        }

    void deleteText(int k) {
            if(findCursor()>k)
            ans.erase(findCursor()-k,k);
            else
            ans=ans.substr(findCursor());

        }


    int findCursor() {

            return ans.find('^');
        }

    void cursorLeft(int k) {
            int pos=findCursor();
            ans=ans.erase(pos,1);

            if(!(pos-k<0))
           {
            ans=ans.substr(0,pos-k)+"^"+ans.substr(pos-k);
           }
           else
            {
            ans="^"+ans;
            }


        }

     void cursorRight(int k) {

            int pos=findCursor();
            ans=ans.erase(pos,1);

            if(!((pos+k)>(ans.size()-1)))
           {
            ans=ans.substr(0,pos+k)+"^"+ans.substr(pos+k);
           }
            else
            {
                ans=ans+"^";
            }

        }

    string fullText() {
        ans=ans.erase(findCursor(),1);
        return ans;
    }

    string showText(int k)
    {
        int pos=findCursor();
        ans=ans.erase(pos,1);
        if(pos+k>ans.size())
        return ans.substr(pos);
        else
        return ans.substr(pos,k);
    }
private:
    string ans;
};

int main()
{

    TextEditor editor;
    editor.addText("Hello");
    editor.backspace();
    editor.cursorLeft(2);
    editor.deleteText(3);
    editor.addText("fa");
    editor.cursorRight(3);
    cout<<editor.fullText();


    return 0;
};
