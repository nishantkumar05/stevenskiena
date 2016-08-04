#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

//First compile errors:
// - Semantic errors
//   - used entries[hash].empty() instead of entries[hash].key..empty() where entries are vector
//   - forgot to define destructor
//   - forgot include <vector>
//   - mistyped nullptr as null
//   - Hash function logic
//   - GetLast() could be null
//   - null test crash
// - Syntax errors
//   - forgot << in std::cout 


using Buffer = std::vector<std::string>;

//Candidate for template
//different key types
//empty key
//removal in case of collision
//size of the array
//Address of a class
class HashTable
{
  struct Entry
  {
    std::string key;
    std::string value;
    Entry *n;
    Entry *p;
  };

  using Entries = std::vector<Entry>;

public:
  HashTable() :entries(20000) { }

  Entry* GetLast(const Entry& start)
  {
    const Entry* tmp = &start;
    Entry *ret = nullptr;

    while(tmp) {
      ret = (Entry *)tmp;
      tmp = tmp->n;
    }
    return ret;
  }

  bool Add(const std::string& key, const std::string& value)
  {
    uint32_t hash = Hash(key);
    Entry *e = new Entry{key, value, nullptr, nullptr};

    //fix duplicate keys
    const Entry& tmp = entries[hash];
    if(!tmp.key.empty()) {
      std::cout << "collission detected" << std::endl;
      Entry *last = GetLast(entries[hash]);
      if(last) {
        last->n = e;
        e->p = last;
      } else {
        std::cout << "last is null" << std::endl;
      }
      return true;
    }

    entries[hash] = *e;
    return true;
  }

  void Enumerate()
  {
    for(Entry entry : entries) {
      if(entry.key.empty()) {
        continue;
      }
      std::cout << entry.key <<":" << entry.value;
      Entry *tmp = entry.n;
      while(tmp) {
        std::cout << "  ===>" << tmp->key <<":" << tmp->value;
        tmp = tmp->n;
      }
      std::cout << std::endl << std::endl;
    }
  }

  //void Remove(const std::string& key);

  ~HashTable() { }

  uint32_t Hash(const std::string& str)
  {
    uint32_t hash = 0;
    for(char i : str ) {
      hash = ((hash << 5) ^ i) % 201;
    }
    std::cout << "hash =" << hash << std::endl;
    return hash;
  }
private:

  Entries entries;
};

void ReadFile(const char* f, Buffer& buf)
{
  std::fstream file(f, std::ios_base::in);
  while(!file.eof()) {
    std::string str;
    file >> str;
    buf.push_back(str);
  }
  file.close();
}

int main(int argc, const char **argv)
{
  if(argc < 2) {
    std::cout << "please provide input file" << std::endl;
    return -1;
  }

	Buffer buf;
  ReadFile(argv[1], buf);

  HashTable h;
  for(auto str : buf ) {
    std::cout << "Adding = " <<str << std::endl;
    h.Add(str, "StupidVal");
  }
  h.Enumerate();

  return 0;
}
