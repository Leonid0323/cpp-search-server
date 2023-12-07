#include"document.h"


Document::Document(int id, double relevance, int rating)
    : id(id)
    , relevance(relevance)
    , rating(rating) {
}

std::ostream&  operator<<(std::ostream& output, const Document& document) {
    const auto [id, relevance, rating] = document;
    output << "{ "s
         << "document_id = "s << id << ", "s
         << "relevance = "s << relevance << ", "s
         << "rating = "s << rating << " }"s;
    return output;
}