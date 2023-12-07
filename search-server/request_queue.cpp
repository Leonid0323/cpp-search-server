#include"request_queue.h"


RequestQueue::RequestQueue(const SearchServer& search_server) 
    :search_server_(search_server){}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    std::vector<Document> matched_documents = search_server_.FindTopDocuments(raw_query, status);
    AddRequest(matched_documents.size()!=0);
    return matched_documents;
}

    std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    std::vector<Document> matched_documents = search_server_.FindTopDocuments(raw_query);
    AddRequest(matched_documents.size()!=0);
    return matched_documents;
}

int RequestQueue::GetNoResultRequests() const {
    return count_if(requests_.begin(), requests_.end(), [](QueryResult query_res){return query_res.request_result == false;});
}

void RequestQueue::AddRequest(bool have_found_queries){
    if(requests_.empty()){
        requests_.push_back({1, have_found_queries});
    } else{
        requests_.push_back({requests_.back().time+1, have_found_queries});
    }
    if(requests_.back().time-requests_.front().time + 1> min_in_day_){
        requests_.pop_front();
    }
}