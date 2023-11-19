/*
    int count = urn.end() - urn.begin();         //4
    int vcount = v.end() - v.begin();            //4
    cout << count << endl;                
    cout << vcount << endl;

    count = urn.rend() - urn.rbegin();     //4
    vcount = v.rend() - v.rbegin();        //4
    cout << count << endl;                
    cout << vcount << endl;

    count = urn.rbegin() - urn.rend();     //-4
    vcount = v.rbegin() - v.rend();        //-4
    cout << count << endl;                
    cout << vcount << endl;


    count = urn.begin() - urn.end();     //-4
    vcount = v.begin() - v.end();        //-4
    cout << count << endl;                
    cout << vcount << endl;
    
    
    cout << "Problem bei:" << endl;
    auto it {urn.begin()};
    it -= 3;
    int count = urn.end() - it;

    auto itv {v.begin()};
    itv -= 3;
    int vcount = v.end() - itv;

    cout << count << endl;                //5
    cout << vcount << endl;                //7
    
    
    cout << to_string(*--it) << endl;
    cout << it.ordinalnumber() << endl;
    cout << it.status() << endl;
    cout << to_string(*--it) << endl;
    cout << it.ordinalnumber() << endl;
    cout << it.status() << endl;
    cout << to_string(*--it) << endl;
    */
    /*
    cout << it.ordinalnumber() << endl;
    cout << it.status() << endl;
    cout << to_string(*++it) << endl;
    cout << it.ordinalnumber() << endl;
    cout << it.status() << endl;
    cout << to_string(*++it) << endl;
    cout << it.ordinalnumber() << endl;
    cout << it.status() << endl;
    cout << to_string(*++it) << endl;
    cout << it.ordinalnumber() << endl;
    cout << it.status() << endl;
    cout << to_string(*++it) << endl;
    */



    /*
    auto it1 {urn.begin()};
    auto it2 {urn.end()};

    auto itv1 {v.begin()};
    auto itv2 {v.end()};

    cout << boolalpha << (it1 == it2) << endl;
    cout << boolalpha << (it1 != it2) << endl;
    cout << boolalpha << (it1 < it2) << endl;
    cout << boolalpha << (it1 > it2) << endl;
    cout << boolalpha << (it1 <= it2) << endl;
    cout << boolalpha << (it1 >= it2) << endl;
    cout << endl;
    cout << boolalpha << (itv1 == itv2) << endl;
    cout << boolalpha << (itv1 != itv2) << endl;
    cout << boolalpha << (itv1 < itv2) << endl;
    cout << boolalpha << (itv1 > itv2) << endl;
    cout << boolalpha << (itv1 <= itv2) << endl;
    cout << boolalpha << (itv1 >= itv2) << endl;

    /*
    auto it {urn.begin()};
    cout << to_string(it[2.6]) << endl;

    auto itv {v.begin()};
    cout << itv[2.3] << endl;


    /*
    int count = urn.end() - urn.begin();
    int vcount = v.end() - v.begin();
    
    int count = urn.rend() - urn.rbegin();
    int vcount = v.rend() - v.rbegin();

    int count = urn.rbegin() - urn.rend();
    int vcount = v.rbegin() - v.rend();
    
    int count = urn.begin() - urn.end();
    int vcount = v.begin() - v.end();
      
    cout << count << endl;
    cout << vcount << endl;


    auto it {urn.begin()};
    it -= 3;
    int count = urn.end() - it;

    auto itv {v.begin()};
    itv -= 3;
    int vcount = v.end() - itv;

    cout << count << endl;
    cout << vcount << endl;

    /*
    cout << "+= und -=" << endl;
    auto it {urn.begin()};
    cout << to_string(*it) << endl;
    it += 2;
    cout << to_string(*it) << endl;
    it -= 1;
    cout << to_string(*it) << endl;
    it -= 0;
    cout << to_string(*it) << endl;

    cout << "+ und -" << endl;
    auto it1 {urn.begin()};
    cout << to_string(*it1) << endl;
    it1 = it1 + 2;
    cout << to_string(*it1) << endl;
    it1 = it1 - 1;
    cout << to_string(*it1) << endl;
    it1 = it1 - 0;
    cout << to_string(*it1) << endl;
    
    /*
    auto it {urn.begin()};

    cout << to_string(*--it) << endl;
    cout << it.ordinalnumber() << endl;
    cout << to_string(*--it) << endl;
    cout << it.ordinalnumber() << endl;

    while(it != urn.end())
    {
        cout << to_string(*it) << endl;
        ++it;
    }

    auto it1 {urn.end()};
    auto it2 {urn.end()};
    cout << "--it" << endl;
    cout << to_string(*--it1) << endl;
    cout << to_string(*--it1) << endl;
    cout << to_string(*--it1) << endl;
    cout << "it--" << endl;
    cout << to_string(*it2--) << endl;
    cout << to_string(*it2--) << endl;
    cout << to_string(*it2--) << endl;

    auto it3 {urn.begin()};
    auto it4 {urn.begin()};
    cout << "++it" << endl;
    cout << to_string(*++it3) << endl;
    cout << to_string(*++it3) << endl;
    cout << to_string(*++it3) << endl;
    cout << "it++" << endl;
    cout << to_string(*it4++) << endl;
    cout << to_string(*it4++) << endl;
    cout << to_string(*it4++) << endl;

    cout << "Loop begin -> end mit ++it" << endl;
    for(auto it {urn.begin()}; it != urn.end(); ++it)
    {
        cout << to_string(*it) << endl;
    }

    cout << "Loop end -> begin mit --it" << endl;
    for(auto itb {urn.end()}; itb != urn.begin(); --itb)
    {
        cout << to_string(*itb) << endl;
    } 
    
    cout << "Loop begin -> end mit it++" << endl;
    for(auto it {urn.begin()}; it != urn.end(); it++)
    {
        cout << to_string(*it) << endl;
    }

    cout << "Loop end -> begin mit it--" << endl;
    for(auto itb {urn.end()}; itb != urn.begin(); itb--)
    {
        cout << to_string(*itb) << endl;
    }

    auto itbr1 {urn.rbegin()};
    auto itbr2 {urn.rbegin()};

    cout << "++it" << endl;
    cout << to_string(*++itbr1) << endl;
    cout << to_string(*++itbr1) << endl;
    cout << to_string(*++itbr1) << endl;
    cout << "it++" << endl;
    cout << to_string(*itbr2++) << endl;
    cout << to_string(*itbr2++) << endl;
    cout << to_string(*itbr2++) << endl;

    auto itre1 {urn.rend()};
    auto itre2 {urn.rend()};

    cout << "--it" << endl;
    cout << to_string(*--itre1) << endl;
    cout << to_string(*--itre1) << endl;
    cout << to_string(*--itre1) << endl;
    cout << "it--" << endl;
    cout << to_string(*itre2--) << endl;
    cout << to_string(*itre2--) << endl;
    cout << to_string(*itre2--) << endl;

    cout << "Loop rbegin -> rend mit ++it" << endl;
    for(auto it {urn.rbegin()}; it != urn.rend(); ++it)
    {
        cout << to_string(*it) << endl;
    }

    cout << "Loop rend -> rbegin mit --it" << endl;
    for(auto itb {urn.rend()}; itb != urn.rbegin(); --itb)
    {
        cout << to_string(*itb) << endl;
    }
    */