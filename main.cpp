// ------------------------------------------------------------------------------------------------
// Programm "Frequenztransformation"
//   Das Programm demonstriert Eigenschaften der FFT
//   - Der Name des Eingangsbildes wird (ohne ".bmp"-Endung)
//     dem Programm als Argument uebergeben.
//     (Bei Code::Blocks werden die Argumente unter
//      "Project"->"Set programs' arguments..." angegeben)
//
// B. Lang, HS Osnabrueck
// Version Dezember 2016 (RH)
// ------------------------------------------------------------------------------------------------

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "AviWrite.h"
#include "BmpRead.h"
#include "BmpWrite.h"
#include "ConvImg.h"
#include "FFT.h"
#include "Img.h"

#define K 5                 // Startwert fuer die Suche der Grundfrequenz
#define WRITE_AVI false     // AVI ausgeben (=true) oder nicht (=false)

// ------------------------------------------------------------------------------------------------
// Aufgabe 1:
// Zeilentransformation durchfuehren
// ------------------------------------------------------------------------------------------------
// Zeilenweise das Quellbild src in den ori_zeile-Vektor kopieren,
// Fouriertransformation durchfuehren und den Ergebnisvektor fft_zeile im
// zeilentransformierten Bild z_fft_img abspeichern.
// ------------------------------------------------------------------------------------------------
// Parameter:
// [in]  src       : Quellbild
// [out] z_fft_img : In den Zeilen transformiertes Bild
// ------------------------------------------------------------------------------------------------
void zeilentransformation(const Img<complex<double> >& src, Img<complex<double> >& z_fft_img)
{
    // TODO: einkommentieren
    // unsigned int width(src.Width());
    // unsigned int height(src.Height());
    // vector<complex<double> > ori_zeile(width);     // Vektor fuer eine originale Bildzeile
    // vector<complex<double> > fft_zeile(width);     // Vektor fuer eine FFT-transformierte Bildzeile

    // TODO: Ihr Code
}

// ------------------------------------------------------------------------------------------------
// Aufgabe 2:
// Die Spektren aller Zeilen zusammenfassen (addieren)
// ------------------------------------------------------------------------------------------------
// Parameter:
// [in]  z_fft_img      : Zeilentransformiertes Bild
// [out] Summenspektrum : Summe der Spektren aller Zeilen
// ------------------------------------------------------------------------------------------------
void summenspektrum_berechnen(const Img<complex<double> >& z_fft_img, vector<double>& Summenspektrum)
{
    // TODO: einkommentieren
    // unsigned int width(z_fft_img.Width());
    // unsigned int height(z_fft_img.Height());

    // TODO: Ihr Code
}

// ------------------------------------------------------------------------------------------------
// Aufgabe 2:
// Im aufsummierten Spektrum die Grundfrequenz suchen
// ------------------------------------------------------------------------------------------------
// Parameter:
// [in]  Summenspektrum : Summe der Spektren aller Zeilen
// [in]  k             : Startwert fuer Frequenzsuche
// [out] f_max         : Position der gefundenen Grundfrequenz im Spektrum
// ------------------------------------------------------------------------------------------------
void grundfrequenz_ermitteln(const vector<double>& Summenspektrum, unsigned int k, unsigned int &f_max)
{
    // TODO: Ihr Code
}

// ------------------------------------------------------------------------------------------------
// Aufgabe 3:
// Pro Zeile nur Mittelwert und Grundfrequenz beibehalten und zurueck in den
// Originalraum transformieren
// ------------------------------------------------------------------------------------------------
// Parameter:
// [in]  z_fft_img : Zeilentransformiertes Bild
// [in]  f_max     : Position des Maximums
// [out] ifft_src  : Ruecktransformiertes Bild aus Gleichanteil und Grundfrequenz
// ------------------------------------------------------------------------------------------------
void grundfrequenzbild_erstellen(const Img<complex<double> >& z_fft_img, unsigned int f_max, Img<unsigned char>& ifft_src)
{
    // TODO: einkommentieren
    // const unsigned int width(z_fft_img.Width());
    // const unsigned int height(z_fft_img.Height());
    // vector<complex<double> > fft_zeile(width, 0);
    // vector<complex<double> > ori_zeile(width);     // Hilfsvektor fuer eine originale Bildzeile

    // TODO: Ihr Code
}

// ------------------------------------------------------------------------------------------------
// Aufgabe 4: Spaltentransformation durchfuehren
// ------------------------------------------------------------------------------------------------
// Parameter:
// [in]  src       : Quellbild
// [out] s_fft_img : In den Spalten transformiertes Bild
// ------------------------------------------------------------------------------------------------
void spaltentransformation(const Img<complex<double > >& src, Img<complex<double> >& s_fft_img)
{
    // TODO: einkommentieren
    // unsigned int width(src.Width());
    // unsigned int height(src.Height());

    // TODO: Ihr Code
}

// ------------------------------------------------------------------------------------------------
// Aufgabe 5: Eine Schicht von FFT-Koeffizienten hinzufuegen
// ------------------------------------------------------------------------------------------------
// Parameter:
// [in]  fft_img     : Fouriertransformiertes Bild in Zeilen und Spalten
// [in]  f           : Index der hinzuzufuegenden Koeffizientenschicht
// [out] fft_img_inc : Fouriertransformiertes Bild mit einem Teil der Koeffizienten
// ------------------------------------------------------------------------------------------------
void schicht_hinzufuegen(const Img<complex<double> >& fft_img, int f, Img<complex<double> >& fft_img_inc)
{
    // TODO: Ihr Code
}

// ------------------------------------------------------------------------------------------------
// Hauptprogramm
// ------------------------------------------------------------------------------------------------
// Parameter:
// [in] argv[1] : Name des Eingangsbildes
// ------------------------------------------------------------------------------------------------
int main(int argc, char*argv[])
{
    string filename;

    cout << "BV-Praktikum: Frequenztransformation" << endl << endl;

    // --------------------------------------------------------------------------------
    // Bildaufnahme
    // --------------------------------------------------------------------------------
    if (argc < 2)
    {
        cerr << "Dateiname nicht angegeben" << endl;
        return -1;
    }

    string Bildname(argv[1]);

    // Bild einlesen
    Img<RGB_Pixel> rgb;
    try
    {
        filename = Bildname + ".bmp";
        BmpRead(filename.c_str()) >> rgb;
        cout << "Lese Datei: " << filename << endl;
    }
    catch (const char * s)
    {
        cerr << "Fehler beim Lesen von " << filename << ": " << s << endl;
        return -1;
    }

    // --------------------------------------------------------------------------------
    // Grauwert Quellbild erzeugen
    // --------------------------------------------------------------------------------
    const unsigned int width  = rgb.Width();
    const unsigned int height = rgb.Height();
    Img<double> src;

    {
        // Dimensionen des Bildes pruefen
        unsigned int ld;
        unsigned int val;
        for(ld = 0, val = width; val != 0; val = val >> 1)
        {
            ld++;
        }
        if (static_cast<unsigned int>(1 << (ld - 1)) != width)
        {
            cerr << "Bildbreite ist keine Zweierpotenz, fft kann nicht verwendet werden" << endl;
            return -1;
        }
        for(ld = 0, val = height; val != 0; val = val >> 1)
        {
            ld++;
        }
        if (static_cast<unsigned int>(1 << (ld - 1)) != height)
        {
            cerr << "Bildhoehe ist keine Zweierpotenz, fft kann nicht verwendet werden" << endl;
            return -1;
        }
        src = ConvImg<double, RGB_Pixel>(rgb);
    }


    // -----------------------------------------------------
    // Aufgabe 1:
    // Zeilentransformation durchfuehren
    // -----------------------------------------------------
    Img<complex<double> > z_fft_img(width, height);

    {
        Img<complex<double> > src_complex(width, height);
        for(unsigned int y = 0; y < height; y++)
        {
            for(unsigned int x = 0; x < width; x++)
            {
                src_complex[y][x] = src[y][x];
            }
        }
        zeilentransformation(src_complex, z_fft_img);

        // Betragsbild erzeugen und ausgeben
        Img<double> z_fft_mag(width, height);
        double Minimum = abs(z_fft_img[0][0]);
        double Maximum = abs(z_fft_img[0][0]);
        for(unsigned int y = 0; y < height; y++)
        {
            for(unsigned int x = 0; x < width; x++)
            {
                double mag = abs(z_fft_img[y][x]);
                if(mag > Maximum)
                    Maximum = mag;
                if(mag < Minimum)
                    Minimum = mag;
                z_fft_mag[y][x] = mag;
            }
        }
        Img<unsigned char> uc_z_fft_mag = ConvImg<unsigned char, double>(z_fft_mag, 255.0 / (Maximum - Minimum), - Minimum);
        try
        {
            filename = Bildname + "_z_fft_mag.bmp";
            BmpWrite(filename.c_str(), uc_z_fft_mag);
            cout << "Schreibe Datei: " << filename << endl;
        }
        catch (const char * s)
        {
            cerr << "Fehler beim Schreiben von " << filename << ": " << s << endl;
            return -1;
        }
    }

    // ----------------------------------------------------------------------------------------------------------
    // Aufgabe 2:
    // Die Spektren aller Zeilen zusammenfassen (addieren) und im aufsummierten Spektrum die Grundfrequenz suchen
    // ----------------------------------------------------------------------------------------------------------
    vector<double> summenspektrum(width);
    unsigned int f_max;    // Position des Maximums

    {
        filename = Bildname + "_summenspektrum.csv";
        ofstream spsum(filename.c_str());
        if(!spsum.is_open())
        {
            cerr << "Fehler beim Oeffnen von " << filename << ": " << strerror(errno) << endl;
            return -1;
        }

        summenspektrum_berechnen(z_fft_img, summenspektrum);

        // Summenspektrum in .csv-Datei schreiben
        for (unsigned int x = 0; x < width; x++)
        {

            ostringstream oss;
            oss << summenspektrum[x];
            string s(oss.str());
            replace(s.begin(), s.end(), '.', ',');
            spsum << s << endl;
        }

        cout << "Schreibe Datei: " << filename << endl;

        // Suche Maximum
        grundfrequenz_ermitteln(summenspektrum, K, f_max);
        cout << "Grundfrequenz: " << f_max << " Perioden. Dies entspricht " << double(width) / double(f_max) << " Pixel pro Periode." << endl;
    }

    // ----------------------------------------------------------------------------------------------------------
    // Aufgabe 3:
    // Pro Zeile nur Mittelwert und Grundfrequenz beibehalten und zurueck in den Originalraum transformieren
    // ----------------------------------------------------------------------------------------------------------
    Img<unsigned char> ifft_src(width, height); // Kopie des zeilentransformierten Bilds nur mit Mittelwert und Grundfrequenz
    grundfrequenzbild_erstellen(z_fft_img, f_max, ifft_src);
    try
    {
        filename = Bildname + "_ifft_src.bmp";
        BmpWrite(filename.c_str(), ifft_src);
        cout << "Schreibe Datei: " << filename << endl;
    }
    catch (const char * s)
    {
        cerr << "Fehler beim Schreiben von " << filename << ": " << s << endl;
        return -1;
    }

    // ----------------------------------------------------------------------------------------------------------
    // Aufgabe 4:
    // Das zeilentransformierte Bild nun auch in den Spalten transformieren
    // ----------------------------------------------------------------------------------------------------------
    Img<complex<double> > fft_img(width, height); // FFT-transformiertes Bild
    spaltentransformation(z_fft_img, fft_img);

    // Betragsbild auf 256 Graustufen skalieren und ausgeben
    {
        Img<double> fft_mag(width, height); // FFT-transformiertes Bild (nur Betrag)

        // Betragsbild erzeugen und ausgeben
        double Minimum = abs(fft_img[0][0]);
        double Maximum = abs(fft_img[0][0]);
        for(unsigned int y = 0; y < height; y++)
        {
            for(unsigned int x = 0; x < width; x++)
            {
                double mag = abs(fft_img[y][x]);
                if(mag > Maximum)
                    Maximum = mag;
                if(mag < Minimum)
                    Minimum = mag;
                fft_mag[y][x] = mag;
            }
        }

        // Bild auf 256 Graustufen skalieren und ausgeben
        Img<unsigned char> uc_fft_mag = ConvImg<unsigned char, double>(fft_mag, 255.0 / (Maximum - Minimum), - Minimum);
        try
        {
            filename = Bildname + "_fft_mag.bmp";
            BmpWrite(filename.c_str(), uc_fft_mag);
            cout << "Schreibe Datei: " << filename << endl;
        }
        catch (const char * s)
        {
            cerr << "Fehler beim Schreiben von " << filename << ": " << s << endl;
            return -1;
        }

        // Bild in Shifting-Darstellung ausgeben
        Img<unsigned char> uc_fft_mag_shifting(width, height);
        uc_fft_mag.Margin_Cyclic();
        for (unsigned int y = 0; y < height; y++)
        {
            for (unsigned int x = 0; x < width; x++)
            {
                uc_fft_mag_shifting[y][x] = uc_fft_mag[y - height / 2][x - width / 2];
            }
        }
        try
        {
            filename = Bildname + "_fft_mag_shifting.bmp";
            BmpWrite(filename.c_str(), uc_fft_mag_shifting);
            cout << "Schreibe Datei: " << filename << endl;
        }
        catch (const char * s)
        {
            cerr << "Fehler beim Schreiben von " << filename << ": " << s << endl;
            return -1;
        }
    }

#if !WRITE_AVI
    return 0;
#endif

    // ----------------------------------------------------------------------------------------------------------
    // Aufgabe 5:
    // Beginnend mit dem Mittelwert die Frequenzen schrittweise in ein Ausgabebild kopieren
    // und in den Originalraum transformieren.
    // Die Bilder im Originalraum werden dann zu einem AVI-Film zusammengestellt.
    // ----------------------------------------------------------------------------------------------------------
    try
    {
        filename = Bildname + "_frequenzanalyse.avi";
        AviWrite avi(filename.c_str(), width, height, 5); // AVI-Objekt oeffnen
        cout << "Schreibe Datei: " << filename << ":   0%";

        Img<complex<double> > fft_img_inc(width, height);  // FFT-transformiertes Bild, dem schrittweise die Frequenzkoeffizienten zugewiesen werden
        Img<complex<double> > src_img_i;                   // R�cktransformiertes complex-Originalbild
        Img<RGB_Pixel>        rgb_src_img_i(width, height); // R�cktransformiertes rgb-Originalbild
        fft_img_inc = complex<double>(0, 0);     // Alle Pixel zu 0 setzen
        rgb_src_img_i = RGB_Pixel(255, 255, 255); // Alle Pixel zu weiss setzen
        fft_img.Margin_Cyclic();                 // Randbehandlung einstellen
        fft_img_inc.Margin_Cyclic();             // Randbehandlung einstellen
        rgb_src_img_i.Margin_Cyclic();           // Randbehandlung einstellen

        // Mittelwert r�cktransformieren
        fft_img_inc[0][0] = fft_img[0][0];  // Koefizient 0,0 (Mittelwert) kopieren
        src_img_i = iFFT_2D(fft_img_inc);   // Bild vom FFT-Raum in den Originalraum zuruecktransformieren
        // complex-Bild in Grauwertbild in RGB-Darstellung konvertieren
        for (unsigned int y = 0; y < height; y++)
        {
            for (unsigned int x = 0; x < width; x++)
            {
                unsigned char val = 256 * src_img_i[y][x].real();
                if (val < 0)
                {
                    val = 0;
                }
                if (val > 255)
                {
                    val = 255;
                }
                rgb_src_img_i[y][x] = RGB_Pixel(val, val, val);
            }
        }
        // Bild in AVI-Datei einschreiben
        avi << rgb_src_img_i;

        // Frequenzkoeffizienten schrittweise umkopieren und Teil-FFT-Bild ruecktransformieren
        for (unsigned int f = 1; f <= width / 2; f++)
        {

            cout << "\b\b\b\b" << std::setw(3) << f * 2 * 100 / width << "%";
            // Quadratische Schicht um 0,0 mit Abstand f aus fft_img in fft_img_inc umkopieren,
            // dann inverse Fouriertransformation vornehmen.
            schicht_hinzufuegen(fft_img, f, fft_img_inc);
            src_img_i = iFFT_2D(fft_img_inc);

            // complex-Bild src_img_i im Originalraum in Grauwertbild in RGB-Darstellung konvertieren
            for (unsigned int y = 0; y < height; y++)
            {
                for (unsigned int x = 0; x < width; x++)
                {
                    int val = 256.0 * src_img_i[y][x].real();
                    if (val < 0)
                    {
                        val = 0;
                    }
                    if (val > 255)
                    {
                        val = 255;
                    }
                    rgb_src_img_i[y][x] = RGB_Pixel(val, val, val);
                }
            }
            // Bild in AVI-Datei einschreiben
            avi << rgb_src_img_i;
        }

        cout << endl;

    }
    catch (char const* s)
    {
        cerr << "Fehler beim Schreiben von " << filename << ": " << s << endl;
    }

    return 0;
}
