// Datastructures.hh
//
// Student name:Maureen Wanjiku Githaiga


#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
using Distance = int;

// Return values for cases where required thing was not found
AffiliationID const NO_AFFILIATION = "---";
PublicationID const NO_PUBLICATION = -1;
Name const NO_NAME = "!NO_NAME!";
Year const NO_YEAR = -1;
Weight const NO_WEIGHT = -1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};


// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};
//my edit This is struct for affiliations
const std::string EMPTY = "";
struct Affiliation
{
    AffiliationID AffiliationID_= EMPTY;
    Name Name_ = EMPTY;
    Coord Coordinate_;

};

//my edit this is struct coordinates for publications

struct Publication
{
    PublicationID PublicationID_ = 0;
    Year Year_ = 0;
    Name Name_ = EMPTY;
    Publication* parent_ = nullptr;//publication which is referenced by this publication
    std::vector<PublicationID> references_ = {};//its children
    std::vector<AffiliationID> affiliations_ = {};
    //std::unordered_set<AffiliationID> affiliations_;

};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:O(1)
    // Short rationale for estimate: size of unordered map takes constant time.
    unsigned int get_affiliation_count();

    // Estimate of performance:O(n)
    // Short rationale for estimate:clearing vector, unordered map and map is linear in size
    void clear_all();

    // Estimate of performance:O(n)
    // Short rationale for estimate:function returns all elements in vector
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance:O(n)
    // Short rationale for estimate:lookup in unordered map can be O(n) worstcase.
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance:O(n)
    // Short rationale for estimate:lookup in unordered map
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:lookup in unordered map
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:O(n)
    // Short rationale for estimate: funcion iterates through elements in map
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance:O(n log n)
    // Short rationale for estimate: inserting in map
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance:O(log n)
    // Short rationale for estimate:finding element in  map
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance:O(n)
    // Short rationale for estimate:find in unordered map .
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:O(n)
    // Short rationale for estimate:find takes linear time
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> & affiliations);

    // Estimate of performance:O(n)
    // Short rationale for estimate:iterates through the vectorof ids
    std::vector<PublicationID> all_publications();

    // Estimate of performance:O(n)
    // Short rationale for estimate:find for unordered map
    Name get_publication_name(PublicationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:find for unordered map
    Year get_publication_year(PublicationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:find for unordered map and returning vector
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:find for unordered map
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance:O(n)
    // Short rationale for estimate:lookup in unordered map
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:look up in unordered map
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance:O(n)
    // Short rationale for estimate:function call performs a linear search
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate: function call find is linear to the container size
    PublicationID get_parent(PublicationID id);

    // Estimate of performance:O(n log n)
    // Short rationale for estimate: function call sort has n log n complexity
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance:O(n)
    // Short rationale for estimate:function call to search is linear
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);


    // Non-compulsory operations

    // Estimate of performance:O(n)
    // Short rationale for estimate:function call to search is linear
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance:O(n)
    // Short rationale for estimate:iterating the elements in the container to remove said id
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance:O(n)
    // Short rationale for estimate:iterating the elements in the container to remove said id
    bool remove_publication(PublicationID publicationid);


private:
    //data structure to store affiliations
    std::unordered_map<AffiliationID,Affiliation*> affiliations_;
    std::vector<AffiliationID>affiliation_ids_;
    std::map<Name,AffiliationID>affiliation_names_;
    std::map<Coord,AffiliationID>affiliation_coordinates_;
    std::vector<AffiliationID> affiliations_alphabetically_;
    std::vector<AffiliationID> affiliations_distance_increasing_;



    //store affiliations for alphabetical and coordinate based sorting
   //std::vector<Affiliation*>affiliationsvector_;
    //store the id positions in the affiliations vector for retrieval
    //std::unordered_map<AffiliationID,size_t>id_positionvector_;//not used
    //publications
    std::unordered_map<PublicationID,Publication*> publications_;
    std::vector<PublicationID>publication_ids_;
    std::unordered_map<AffiliationID,std::vector<PublicationID>>affiliation_publication_;

    std::unordered_map<PublicationID, std::vector<PublicationID>> referenced_by_;

    double calculate_distance(Coord coordinate);
    double calculate_distance_between(Coord coordinate_a,Coord coordinate_b);



};

#endif // DATASTRUCTURES_HH
