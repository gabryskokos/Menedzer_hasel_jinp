#include "MenedzerHasel.h"
#include <fstream>
#include <iostream>

MenedzerHasel::MenedzerHasel(std::shared_ptr<BazowySzyfrator> s, std::shared_ptr<BazowyWalidator> w) 
    : szyfrator(s), walidator(w) {
    wczytajZPliku();
}

void MenedzerHasel::wczytajZPliku() {
    std::ifstream plik("baza_hasel.txt");
    std::string s, l, h;
    
    while (plik >> s >> l >> h) {
        listaHasel.push_back({s, l, h});
    }
    plik.close();
}

bool MenedzerHasel::dodajHaslo(std::string s, std::string l, std::string h) {
    if (walidator->czyJestSilne(h)) {
        WpisHasla nowyWpis;
        nowyWpis.serwis = s;
        nowyWpis.login = l;
        nowyWpis.zaszyfrowaneHaslo = szyfrator->szyfruj(h);

        listaHasel.push_back(nowyWpis);

        std::ofstream plik("baza_hasel.txt", std::ios::app);
        plik << nowyWpis.serwis << " " << nowyWpis.login << " " << nowyWpis.zaszyfrowaneHaslo << "\n";
        plik.close();

        return true;
    }
    return false;
}

std::vector<OdszyfrowanyWpis> MenedzerHasel::pobierzWszystkie() {
    std::vector<OdszyfrowanyWpis> wynik;
    for (const auto& wpis : listaHasel) {
        wynik.push_back({wpis.serwis, wpis.login, szyfrator->deszyfruj(wpis.zaszyfrowaneHaslo)});
    }
    return wynik;
}