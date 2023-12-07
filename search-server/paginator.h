#pragma once
#include<algorithm>
#include<iostream>
#include <vector>

#include"document.h"


using namespace std::string_literals;


template <typename Iterator>
class IteratorRange{
public:
    explicit IteratorRange(Iterator range_begin, Iterator range_end)
    : page_begin_(range_begin), page_end_(range_end){
    }
    
    Iterator begin() const{
        return page_begin_;
    }
    Iterator end() const{
        return  page_end_;
    }
    size_t size() const{
        return page_end_ - page_begin_;
    }
private:
    Iterator page_begin_;
    Iterator page_end_;
};

template <typename Iterator>
class Paginator {
public:
    explicit Paginator(Iterator range_begin, Iterator range_end, size_t page_size){
        auto iter = range_begin;
        while(true){
            if(distance(iter, range_end) >page_size){
                IteratorRange<Iterator> page(iter, iter+page_size);
                pages_.push_back(page);
                advance(iter, page_size);
            } else{
                IteratorRange<Iterator> page(iter, range_end);
                pages_.push_back(page);
                break;
            }
        }
    }
    auto begin() const{
        return pages_.begin();
    }
    auto end() const{
        return pages_.end();
    }
    size_t size() const{
        return pages_.size();
    }
private:
    std::vector<IteratorRange<Iterator>> pages_;
};

std::ostream&  operator<<(std::ostream& output, const Document& document) {
    const auto [id, relevance, rating] = document;
    output << "{ "s
         << "document_id = "s << id << ", "s
         << "relevance = "s << relevance << ", "s
         << "rating = "s << rating << " }"s;
    return output;
}
 
template<typename It>
std::ostream&  operator<<(std::ostream& output, const IteratorRange<It>& pages) {
    for (auto page = pages.begin(); page != pages.end(); page++) {
        output << *page;
    }
    return output;
}

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator<typename Container::const_iterator>(begin(c), end(c), page_size);
}