//
//  list.cpp
//  hw4
//
//  Created by Aditya Pimplaskar on 3/1/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

void listAll(const MenuItem* m, string path) // two-parameter overload
{
    //The idea here is that we will start out with an empty path and m being just one node
    //We will add that node to the path and recursively call on the next node with the new path
    /* SHOULD RETURN
     File
     File/New
     File/New/Window
     File/Open
     File/Exit
     Refresh
     Under Development
     Help
     Help/Index
     Help/About
     */
    
    //Base case
    if(m->menuItems() == nullptr) {return; }
    if (m->menuItems()->size() < 1){ return; }
    
    vector<MenuItem*>::const_iterator it = m->menuItems()->begin();
    while(it != m->menuItems()->end()){
        cout << path + (*it)->name() << endl;
        listAll((*it), path + (*it)->name() + "/");
        it++;
    }
}
