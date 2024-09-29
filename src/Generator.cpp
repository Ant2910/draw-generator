#include <iostream>
#include <string>
#include <cmath>

using namespace std;

unsigned long long factorial(const unsigned int& n)
{   
    unsigned long long result {1};
    for(unsigned int nCount {n}; nCount >= 1; --nCount)
    {
        result *= nCount;
    }
    return result;
}


unsigned int sizeUrnO(const unsigned int& n, const unsigned int& k)
{   
    if(k == 0)
    {
        return 0;
    }
    return (factorial(n)/factorial(n-k));
}
unsigned int sizeUrnR(const unsigned int& n, const unsigned int& k)
{   
        
    if(k == 0)
    {
        return 0;
    }
    return ((factorial(k+n-1))/(factorial(k)*factorial(n-1)));
}

unsigned int sizeUrn(const unsigned int& n, const unsigned int& k)
{   
    if(k == 0)
    {
        return 0;
    }
    return ((factorial(n))/(factorial(n-k)*factorial(k)));
}

unsigned int sizeUrnOR(const unsigned int& n, const unsigned int& k) 
{   
    if(k == 0)    
    {
        return 0;
    }
    return static_cast<unsigned int>(std::pow(n,k));
}



int main() 
{
    char wiederholung {}, reihenfolge {}, vorgeneriert {}, verwendung {};
    unsigned int n {}, k {};


    // Benutzerabfragen
    bool validWiederholung = true;
    do{
        cout << "Ist Wiederholung wichtig? (J/N): ";
        cin >> wiederholung;

        if(wiederholung == 'j' || wiederholung == 'J' || wiederholung == 'n' || wiederholung == 'N')
        {     
            validWiederholung = false;
        }
        else
        {
            cout << "Eingabe nicht valide. Bitte mit J oder N antworten" << endl;
        }

    }while(validWiederholung);
    

    bool validReihenfolge = true;
    do{
        cout << "Ist die Reihenfolge der gezogenen Werte wichtig? (J/N): ";
        cin >> reihenfolge;

        if(reihenfolge == 'j' || reihenfolge == 'J' || reihenfolge == 'n' || reihenfolge == 'N')
        {   
            validReihenfolge = false;
        }
        else
        {
            cout << "Eingabe nicht valide. Bitte mit J oder N antworten" << endl;
        }

    }while(validReihenfolge);

    cout << "Wie groß ist n (Gesamtanzahl der Objekte)?: ";
    cin >> n;

    cout << "Wie groß ist k (Anzahl der gezogenen Objekte)?: ";
    cin >> k;

    cout << "Was ist der Verwendungszweck (Vorwärts Iteration = f/Rückwärts = r/Spezifscher Zug = s)?: ";
    cin >> verwendung;

    cout << "Sollen die Züge vorgeneriert werden? (J/N)?: ";
    cin >> vorgeneriert;

    // Bestimmung des Urnentypen
    string urnTyp {};

    if(reihenfolge == 'j' || reihenfolge == 'J' && wiederholung == 'j' || wiederholung == 'J') 
    {
        urnTyp = "UrnOR";
    } 
    else if(reihenfolge == 'n' || reihenfolge == 'N' && wiederholung == 'j' || wiederholung == 'J') 
    {
        urnTyp = "UrnO";
    } 
    else if(reihenfolge == 'j' || reihenfolge == 'J' && wiederholung == 'n' || wiederholung == 'N') 
    {
        urnTyp = "UrnR";
    } 
    else if(reihenfolge == 'n' || reihenfolge == 'N' && wiederholung == 'n' || wiederholung == 'N') 
    {
        urnTyp = "Urn";
    }

    // Bestimmung der Urnengröße
    string urnGröße {};
    if(urnTyp == "UrnOR")
    {
        if(sizeUrnOR(n,k) > 27)
        {
            urnGröße = "big";
        }else
        {
            urnGröße = "small";
        }
    }
    else if(urnTyp == "UrnO")
    {
        if(sizeUrnO(n,k) > 6)
        {
            urnGröße = "big";
        }else
        {
            urnGröße = "small";
        }
    }
    else if(urnTyp == "UrnR")
    {
        if(sizeUrnR(n,k) > 10)
        {
            urnGröße = "big";
        }else
        {
            urnGröße = "small";
        }
    }
    else if(urnTyp == "Urn")
    {
        if(sizeUrn(n,k) > 6)
        {
            urnGröße = "big";
        }else
        {
            urnGröße = "small";
        }
    }

    // Bestimmung der Urnenimplementation
    string urnImplementation {};

    if(vorgeneriert == 'n' || vorgeneriert == 'N')
    {
        if(verwendung == 'f')
        {   
            //small
            if(urnTyp == "UrnOR" && urnGröße == "small")
            {
                urnImplementation = "urn::UrnOR";
            }
            else if(urnTyp == "UrnO" && urnGröße == "small")
            {
                urnImplementation = "urn::UrnO";
            }
            else if(urnTyp == "UrnR" && urnGröße == "small")
            {
                urnImplementation = "urn::UrnR";
            }
            else if(urnTyp == "Urn" && urnGröße == "small")
            {
                urnImplementation = "urn::Urn";
            }

            //big
            if(urnTyp == "UrnOR" && urnGröße == "big")
            {
                urnImplementation = "na::naive_approach_UrnOR";
            }
            else if(urnTyp == "UrnO" && urnGröße == "big")
            {
                urnImplementation = "discreture::permutation";
            }
            else if(urnTyp == "UrnR" && urnGröße == "big")
            {
                urnImplementation = "na::naive_approach_UrnR";
            }
            else if(urnTyp == "Urn" && urnGröße == "big")
            {
                urnImplementation = "na::naive_approach_Urn";
            }
        }
        else if(verwendung == 'r')
        {   
            //small
            if(urnTyp == "UrnOR" && urnGröße == "small")
            {
                urnImplementation = "urn::UrnOR";
            }
            else if(urnTyp == "UrnO" && urnGröße == "small")
            {
                urnImplementation = "urn::UrnO";
            }
            else if(urnTyp == "UrnR" && urnGröße == "small")
            {
                urnImplementation = "urn::UrnR";
            }
            else if(urnTyp == "Urn" && urnGröße == "small")
            {
                urnImplementation = "urn::Urn";
            }

            //big
            if(urnTyp == "UrnOR" && urnGröße == "big")
            {
                urnImplementation = "na::naive_approach_UrnOR";
            }
            else if(urnTyp == "UrnO" && urnGröße == "big")
            {
                urnImplementation = "std::prev_permutation";
            }
            else if(urnTyp == "UrnR" && urnGröße == "big")
            {
                urnImplementation = "na::naive_approach_UrnR";
            }
            else if(urnTyp == "Urn" && urnGröße == "big")
            {
                urnImplementation = "discreture::combinations";
            }
        }
        else if(verwendung = 's')
        {   
            //small
            if(urnTyp == "UrnOR" && urnGröße == "small")
            {
                urnImplementation = "na::naive_approach_UrnOR";
            }
            else if(urnTyp == "UrnO" && urnGröße == "small")
            {
                urnImplementation = "std::next_permutation";
            }
            else if(urnTyp == "UrnR" && urnGröße == "small")
            {
                urnImplementation = "urn::UrnR";
            }
            else if(urnTyp == "Urn" && urnGröße == "small")
            {
                urnImplementation = "urn::Urn";
            }

            //big
            if(urnTyp == "UrnOR" && urnGröße == "big")
            {
                urnImplementation = "urn::UrnOR";
            }
            else if(urnTyp == "UrnO" && urnGröße == "big")
            {
                urnImplementation = "urn:UrnO";
            }
            else if(urnTyp == "UrnR" && urnGröße == "big")
            {
                urnImplementation = "na::naive_approach_UrnR";
            }
            else if(urnTyp == "Urn" && urnGröße == "big")
            {
                urnImplementation = "na::naive_approach_Urn";
            }
        }
    }
    else if(vorgeneriert == 'j' || vorgeneriert == 'J')
    {

    }

    cout << "Die Urnenimplementation: " << urnImplementation << endl;
}