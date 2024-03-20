# Smart City Mobility Management

The essence of this project is the development of a software solution to streamline the management (registration, sharing, use) of urban mobility resources in a smart-city context. The implementation of the solution must take into account dynamic data structures, file storage, modularization and present appropriate structuring and documentation. Considering two types of users, namely managers and registered customers. 

1st Phase:
1. Definition of a dynamic data structure (to be validated in advance with the teacher) to represent the means of electric mobility, customers and managers;
2. Storing/reading data in text files (simulation values) and binary files (preserving data);
3. Inserting new data (customer/manager/electric mobility medium);
4. Removing certain data (client/manager/electric mobility medium);
5. Modifying certain data (client/manager/electric mobility mode);
6. Registering the rental of a particular means of electric mobility;
7. Listing the means of electric mobility in descending order of autonomy;
8. Listing of existing electric mobility vehicles in a location with a given geocode.


Stage 2: 
1. Definition of a dynamic data structure to represent the location of a set of customers and means of electric mobility, using a graph;
2. Storing/reading the data in text files text (simulation values) and binary (preserve data). Given the location of a customer, list the means of electric mobility of a given type that exist within a given radius;
3. Calculate a solution (adaptation of the traveling salesman problem) of the route with the shortest distance to travel, using a truck, to collect all the means of electric mobility with a battery charge of less than 50%. The point of departure and arrival are the same. The truck's transport capacity is limited and depends on the types of mobility equipment being transported, so it may be necessary to make several circuits to complete the collection of these electric mobility equipment.
