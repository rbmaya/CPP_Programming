#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>

using namespace std;

enum errors{
    ALL_RIGHT,
    F_INP_OPEN,
    F_OUT_OPEN
};

static bool compare(const pair <string, int>  &a, const pair <string, int> &b){
    return a.second > b.second;
}

static double frequency(int value, size_t size){
    double freq = (double) value / size * 100;
    return round(freq * 100) / 100;
}


class WordsStat{
public:
    void set(string const & word){
        words[word]++;
        ++weight;
    }

    size_t get_size() const{
        return words_vec.size();
    }

    size_t get_weight() const{
        return weight;
    }

    double get_frequency(const string & word){
        return frequency(words[word], get_weight());
    }

    void sorting(){
        vector<pair<string, int>> words_2(words.begin(), words.end());
        sort(words_2.begin(), words_2.end(), compare);
        words_vec = words_2;
    }

    const pair <string, int> & operator [] (int i) const{
        return words_vec[i];
    }

private:
    map <string, int> words;
    size_t weight = 0;
    vector <pair<string,int>> words_vec;
};


class CSV_Formatter{
public:
    explicit CSV_Formatter(WordsStat & words_stat) : words_stat(words_stat)  {};

    string output() const{
        string out_line;
        int size = words_stat.get_size();
        for (auto i = 0; i != size; ++i) {
            out_line +=  words_stat[i].first;
            out_line += ",";
            out_line += to_string(words_stat[i].second);
            out_line += ",";
            out_line += to_string(words_stat.get_frequency(words_stat[i].first));
            out_line += "%";
            out_line += "\n";
        }
        return out_line;
    }

private:
    WordsStat & words_stat;
};


class Reporter{
public:
    Reporter(WordsStat & words_stat, ofstream & out, CSV_Formatter & formatter) : words_stat(words_stat), out(out), formatter(formatter)  {};

    void get_report(){
        out << "Word, Frequency, Percentage frequency\n";
        out << formatter.output();
    }

public:
    CSV_Formatter formatter;
    WordsStat words_stat;
    ofstream & out;
};


class TokenSplitter{
public:
    explicit TokenSplitter(string & line): line(line) {};

    void split_up(WordsStat & words_stat) const{
        int length = line.length();
        string word;
        for (int i = 0; i < length; ++i){
            if (isalnum(line[i])) word += line[i];
            else if (word.length()){
                words_stat.set(word);
                word.clear();
            }
        }
        if (word.length()) words_stat.set(word);
    }

private:
    string line;
};


class Reader {
public:
    Reader(ifstream & inp, ofstream & out): inp(inp), out(out) {};

    int open_inp_file(char *name) const{
        inp.open(name);
        if (!inp) return F_INP_OPEN;
        return ALL_RIGHT;
    }

    int open_out_file(char *name) const{
        out.open(name);
        if (!out) return F_OUT_OPEN;
        return ALL_RIGHT;
    }
    WordsStat reading() const{
        WordsStat words_stat;
        string line;
        while (!inp.eof()){
            getline(inp, line);
            TokenSplitter splitter(line);
            splitter.split_up(words_stat);
        }
        return words_stat;
    }

private:
    ifstream & inp;
    ofstream & out;
};


class Controller{
public:
    Controller(ifstream & inp, ofstream & out, int & argc, char **argv) : inp(inp), out(out),
        argc(argc), argv(argv){};

    int process(){
        Reader reader(inp, out);
        int err = reader.open_inp_file(argv[1]);
        if (err) return err;

        WordsStat words_stat = reader.reading();

        words_stat.sorting();

        err = reader.open_out_file(argv[2]);
        if (err) return err;

        CSV_Formatter formatter(words_stat);

        Reporter reporter(words_stat, out, formatter);

        reporter.get_report();

        return err;
    }

private:
    ifstream & inp;
    ofstream & out;
    int argc;
    char **argv;
};


int main(int argc, char **argv) {
    ifstream inp;

    ofstream out;

    Controller controller(inp, out, argc, argv);

    int err = controller.process();

    if (err != F_INP_OPEN) {
        inp.close();
        if (err != F_OUT_OPEN) out.close();
    }

    return err;
}
