// Datastructures.cc
//
// Student name:Maureen Wanjiku Githaiga


#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
    for(auto& affiliation : affiliations_)
    {
        delete affiliation.second;
        affiliation.second = nullptr;

    }
    for(auto& publication : publications_)
    {
        delete publication.second;
        publication.second = nullptr;

    }

}

unsigned int Datastructures::get_affiliation_count()
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliation_count()");
    return affiliations_.size();
}

void Datastructures::clear_all()
{
    // Replace the line below with your implementation
    //throw NotImplemented("clear_all()");
     affiliations_.clear();
     affiliation_ids_.clear();
     affiliation_names_.clear();
     affiliation_coordinates_.clear();
     //affiliationsvector_.clear();
     //id_positionvector_.clear();
     publications_.clear();
     publication_ids_.clear();
     affiliation_publication_.clear();
     affiliations_alphabetically_.clear();
     affiliations_distance_increasing_.clear();
     referenced_by_.clear();


}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_all_affiliations()");
    return affiliation_ids_;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy)
{
    // Replace the line below with your implementation
    //throw NotImplemented("add_affiliation()");
    if (affiliations_.find(id)==affiliations_.end()){
        Affiliation* new_affiliation = new Affiliation{id, name, xy};
        affiliation_ids_.push_back(id);
        affiliations_.insert(std::make_pair(new_affiliation->AffiliationID_,new_affiliation));
        affiliation_names_[name] = id;
        affiliation_coordinates_[xy] = id;
        //affiliationsvector_.push_back(new_affiliation);
        affiliations_alphabetically_.clear();
        affiliations_distance_increasing_.clear();
        return true;
    }
    return false;
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliation_name()");

    const auto& it = affiliations_.find(id);
    if(it !=affiliations_.end()){
        return it->second->Name_;
    }
    return NO_NAME;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliation_coord()");

    const auto& it = affiliations_.find(id);
    if(it != affiliations_.end()){
        return it->second->Coordinate_;
    }
    return NO_COORD;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliations_alphabetically()");
    if (affiliations_alphabetically_.empty()) {
        std::vector<AffiliationID> affiliation_ordered;
        affiliations_alphabetically_.reserve(affiliation_names_.size());
        for (const auto& name : affiliation_names_) {
            affiliation_ordered.push_back(name.second);
        }
        affiliations_alphabetically_ = affiliation_ordered;
    }
    return affiliations_alphabetically_;

}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliations_distance_increasing()");

    if (affiliations_distance_increasing_.empty()){
        std::map<std::pair<double, std::pair<double, double>>, AffiliationID> distances;
        std::vector<AffiliationID> affiliation_ids;
        for (auto& affiliation : affiliations_) {
            double distance = calculate_distance(affiliation.second->Coordinate_);
            distances.emplace(std::make_pair(distance, std::make_pair(affiliation.second->Coordinate_.y, affiliation.second->Coordinate_.x)), affiliation.first);
            }
        affiliation_ids.reserve(distances.size());
        for(auto& distances : distances){
            affiliation_ids.push_back(distances.second);
        }
        affiliations_distance_increasing_ = affiliation_ids;
    }
    return affiliations_distance_increasing_;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    // Replace the line below with your implementation
    //throw NotImplemented("find_affiliation_with_coord()");
    const auto& it = affiliation_coordinates_.find(xy);
    if(it == affiliation_coordinates_.end()){
        return NO_AFFILIATION;

    }
      return it->second;
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    // Replace the line below with your implementation
    //throw NotImplemented("change_affiliation_coord()");
    const auto& it = affiliations_.find(id);
    if(it == affiliations_.end()){
         return false;
    }

    //changing in the affiliations map
    Coord xy =  it->second->Coordinate_ ;
    affiliation_coordinates_.erase(xy);
    //changing in the affiliations unordered map
    it->second->Coordinate_= newcoord;
    affiliation_coordinates_.insert({newcoord,it->first});
    affiliations_distance_increasing_.clear();
    return true;

}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> &affiliations)
{
    // Replace the line below with your implementation
    //throw NotImplemented("add_publication()");
    if (publications_.find(id) == publications_.end()){
        Publication* new_publication = new Publication{id,year,name};
        publications_.insert(std::make_pair(new_publication->PublicationID_,new_publication));
        new_publication->affiliations_ = affiliations;
        publication_ids_.push_back(id);
        return true;
    }
    return false;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    // Replace the line below with your implementation
    //throw NotImplemented("all_publications()");
    //vector of publication ids
    return publication_ids_;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_publication_name()");
    const auto& it = publications_.find(id);
    if(it == publications_.end()){
        return NO_NAME;
    }
    return it->second->Name_;
}

Year Datastructures::get_publication_year(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_publication_year()");
    const auto& it = publications_.find(id);
    if(it == publications_.end()){
        return NO_YEAR;
    }
    return it->second->Year_;

}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliations()");
    const auto& publication = publications_.find(id);
    if(publication == publications_.end()){
         return {NO_AFFILIATION};
    }
    return publication->second->affiliations_;

}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    // Replace the line below with your implementation
    //throw NotImplemented("add_reference()");

    const auto& publication = publications_.find(id);
    const auto& parent = publications_.find(parentid);
    if(publication == publications_.end() || parent == publications_.end()){
        return false;
    }
    // the reference from the second publication to the first
    parent->second->references_.push_back(id);

    //the parent reference for the first publication
    publication->second->parent_ = parent->second;
    referenced_by_.clear();
    return true;
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_direct_references()");
    const auto& it = publications_.find(id);
    if(it != publications_.end()){
        return it->second->references_;
    }

    return {NO_PUBLICATION};
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    // Replace the line below with your implementation
    //throw NotImplemented("add_affiliation_to_publication()");
    const auto& publication = publications_.find(publicationid);
    const auto& affiliation = affiliations_.find(affiliationid);


    std::vector<PublicationID>publications = {};
    if(publication == publications_.end() || affiliation == affiliations_.end()){
        return false;
    }
    //if affiliation is already linked to the publication
   auto& affiliation_publication = publication->second->affiliations_;
   if (std::find(affiliation_publication.begin(), affiliation_publication.end(), affiliationid) != affiliation_publication.end()) {
       return false; // Affiliation already linked to this publication
   }
   // update the publication with the new affiliation
   affiliation_publication.push_back(affiliationid);

   // update the reverse mapping: affiliation -> publications
   affiliation_publication_[affiliationid].push_back(publicationid);

   return true;
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_publications()");
    //looking for id in the unordered map that has the publications linked to an affiliation
    if(affiliations_.find(id) == affiliations_.end()){
        return {NO_PUBLICATION};
    }
    return affiliation_publication_[id];

}

PublicationID Datastructures::get_parent(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_parent()");
     const auto& publication = publications_.find(id);
     if(publication != publications_.end()){
         if(publication->second->parent_ != nullptr){
             return publication->second->parent_->PublicationID_;
         }
     }
     return NO_PUBLICATION;
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_publications_after()");

    std::vector<std::pair<Year, PublicationID> > publications_after;

    if (affiliation_publication_.find(affiliationid) == affiliation_publication_.end()){
        return {{NO_YEAR,NO_PUBLICATION}} ;
    }
    //publications for the given affiliation
    const auto& publication_vec = affiliation_publication_[affiliationid];
    //publication id for that given affiliation
    for (const auto& publication_id : publication_vec){

        const auto& publication = publications_[publication_id];
        if(publication->Year_ >= year){
            publications_after.emplace_back(publication->Year_, publication->PublicationID_);
        }
    }

    std::sort(publications_after.begin(), publications_after.end(),
        [](const auto& a, const auto& b) {
            if (a.first == b.first) {
                return a.second < b.second;
            }
            return a.first < b.first;
        });

    return publications_after;
}


std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_referenced_by_chain()");
    if(referenced_by_.count(id) > 0){
        return referenced_by_[id];
    }
    if (publications_.find(id) == publications_.end()){
        return {NO_PUBLICATION};
    }

    std::vector<PublicationID> referenced_by_chain;
    std::set<PublicationID> visited;
    // store a lambda for depth first search
    std::function<void(PublicationID)> get_referenced_by = [&](PublicationID id) {
        visited.insert(id);
        for(const auto& publication : publications_){
            if (std::find(publication.second->references_.begin(), publication.second->references_.end(), id) != publication.second->references_.end() &&
                            visited.find(publication.first) == visited.end()) {
                            referenced_by_chain.push_back(publication.first);
                            get_referenced_by(publication.first);
                        }
                    }
         };
    get_referenced_by(id);
    referenced_by_[id] = referenced_by_chain;
    return referenced_by_chain;
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_all_references()");
    if (publications_.find(id) == publications_.end()) {
            return {NO_PUBLICATION};
    }

    std::vector<PublicationID> all_references;
    std::set<PublicationID> visited;

    //function to traverse references depth first search
    std::function<void(PublicationID)> search_all = [&](PublicationID id) {
        visited.insert(id);
        for (const auto& reference_id : publications_[id]->references_) {
            if (visited.find(reference_id) == visited.end()) {
                all_references.push_back(reference_id);
                search_all(reference_id);
            }
        }
    };

    search_all(id);
    return all_references;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_affiliations_closest_to()");
    std::map<std::pair<double, std::pair<double, double>>, AffiliationID> distances;
    std::vector<AffiliationID> affiliation_ids;
    for (auto& affiliation : affiliations_) {
        double distance = calculate_distance_between(affiliation.second->Coordinate_,xy);
        distances.emplace(std::make_pair(distance, std::make_pair(affiliation.second->Coordinate_.y, affiliation.second->Coordinate_.x)), affiliation.first);
        }

    std::vector<AffiliationID> closest_affiliations;
    closest_affiliations.reserve(std::min<size_t>(3, distances.size()));

    size_t count = 0;
    for (auto it = distances.begin(); count < std::min<size_t>(3, distances.size()); ++it, ++count) {
        closest_affiliations.push_back(it->second);
    }

    return closest_affiliations;
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    // Replace the line below with your implementation
    //throw NotImplemented("remove_affiliation()");
    auto affiliation = affiliations_.find(id);
    if (affiliation == affiliations_.end()) {
        return false;
    }
    // remove the affiliation from all publications
   for (auto& publication : publications_) {
       auto& affiliations = publication.second->affiliations_;
       affiliations.erase(std::remove(affiliations.begin(), affiliations.end(), id), affiliations.end());
   }
   //removing from affiliation names
   auto name = affiliation_names_.find(affiliation->second->Name_);
   if (name != affiliation_names_.end()) {
           affiliation_names_.erase(name);
   }
   //removing from affiliation_coordinates_
   auto coord = affiliation_coordinates_.find(affiliation->second->Coordinate_);
   if (coord != affiliation_coordinates_.end()) {
           affiliation_coordinates_.erase(coord);
   }

   //removing from affiliations map
   delete affiliation->second;
   affiliations_.erase(affiliation);
   return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    // Replace the line below with your implementation
    //throw NotImplemented("get_closest_common_parent()");
      if (publications_.find(id1) == publications_.end() || publications_.find(id2) == publications_.end()) {
        return NO_PUBLICATION;
      }
      std::unordered_set<PublicationID> p1, p2;

      PublicationID curr_id = id1;
      while (curr_id != NO_PUBLICATION) {
          p1.insert(curr_id);
          if (publications_[curr_id]->parent_ == nullptr) {
              return curr_id;
              //break; //if root
            }
          curr_id = publications_[curr_id]->parent_->PublicationID_;
      }

      curr_id = id2;
      while (curr_id != NO_PUBLICATION) {
          if (p1.find(curr_id) != p1.end()) {
              return curr_id;
          }
          if(publications_[curr_id]->parent_ == nullptr) {
              return curr_id;
                //break; //if root
            }
          curr_id = publications_[curr_id]->parent_->PublicationID_;
      }

      return NO_PUBLICATION;

}

bool Datastructures::remove_publication(PublicationID publicationid)
{
    // Replace the line below with your implementation
    //throw NotImplemented("remove_publication()");
    auto publication = publications_.find(publicationid);
    if(publication == publications_.end()){
        return false;
    }
    //removing from references
    for (auto& pub : publications_){
        auto& references = pub.second->references_;
        auto it = std::remove(references.begin(), references.end(), publicationid);
        references.erase(it, references.end());
    }
    // removing affiliations from the publication
    auto& affiliations = publication->second->affiliations_;
    affiliations.clear();
    //removing from affiliation_publications_ unordered map
    for(auto& it : affiliation_publication_){
        auto pub = it.second;
        pub.erase(std::remove(pub.begin(), pub.end(), publicationid), pub.end());

    }
    //removing from vector of ids
    auto id = std::remove(publication_ids_.begin(), publication_ids_.end(), publicationid);
    publication_ids_.erase(id, publication_ids_.end());
    //removing from publications
    delete publication->second;
    publications_.erase(publication);
    return true;
}

double Datastructures::calculate_distance(Coord coordinate)
{
    //calculate euclidean distance from origin
    return sqrt(pow(coordinate.x, 2) + pow(coordinate.y, 2));

}

double Datastructures::calculate_distance_between(Coord coordinate_a, Coord coordinate_b)
{
    //calculate distance between two coordinates
    double x_distance = coordinate_a.x - coordinate_b.x;
    double y_distance = coordinate_a.y - coordinate_b.y;
  return sqrt(pow(x_distance, 2) + pow(y_distance, 2));

}


