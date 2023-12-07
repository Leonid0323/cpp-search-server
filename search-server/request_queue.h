#pragma once
#include"algorithm"
#include<queue>
#include <vector>

#include "document.h"
#include"search_server.h"


class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);

    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        std::vector<Document> matched_documents = search_server_.FindTopDocuments(raw_query, document_predicate);
        AddRequest(matched_documents.size()!=0);
        return matched_documents;
    }

    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);
    int GetNoResultRequests() const;

private:
    struct QueryResult {
        int time;
        bool request_result;
    };
    const SearchServer& search_server_;
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    
    void AddRequest(bool have_found_queries);
};