# The task for the application of the type client-server
Requirements
    •The application is of the client-server type. It works with 3 domain types and implements complete CRUD over them (basic data operations insert, read, update, delete).

Server part
    •Is a three-layer application
    •Is built on the Spring framework and written in Java
    •Uses object-relational mapping in the persistent layer
        •Any relational database with persistent data storage can be used to serve multiple requests (DB server)
        •Therefore, neither in-memory nor a simple built-in file database (e.g. SQLite) is counted
        •Works with at least 3 entities from the relational database (all CRUD operations, min. 1 many-to-many binding, i.e. there will be 4 tables in the relational •Database; using ORM)
        •Using ORM implements an extra query (beyond CRUD and M:N binding manipulation, query implemented ideally in JPQL)
    •Application logic layer allows all data layer operations (CRUD over all entities, M:N binding manipulation, extra query)
    •A well-designed and documented REST API provides access to all operations of the application logic layer (including CRUD over all entities)
        •Compliance with web standards incl. HTTP status
        •Compliance with RESTful policies will be part of the evaluation
        •Complete, well-designed and machine-readable API documentation (ideally OpenAPI): all resources (addresses), operations and data formats
        •A separate data model for the API (the "DTO" classes) is strongly recommended
    •Includes automated tests
        •The three different types of tests discussed in the course
    •Is suitably buildable (Gradle) and tests are run and evaluated as part of the build
    •It is versioned using git
        •The repository hosted on Gitlab FIT (gitlab.fit.cvut.cz/<username>/<server_repo>) should be used for development and commit
Client part
    •Any programming/scripting language
    •Any interface (GUI, web application, interactive console application)
    •Accesses a RESTful web service made available by the server part
    •Implements a complex business operation using the server side
        •This operation (from the point of view of e.g. the user, it is a single action, e.g. triggered by a button in a form) is composed of several sub-steps from the point of view of the system, e.g. database operations or decision (if) on the client side
    •Is versioned
        •The repository hosted on Gitlab FIT (gitlab.fit.cvut.cz/<username>/<client_repo>, this can be the same repository as for the server) should be used for development and commit

The description of my app:
    My restaurant application is designed to manage information about customer orders with delivery. Customers can create food orders, select the type of food, and choose whether to include a tip. The order will also include customer information such as their name, surname, age, and date of birth, as well as the delivery address.

    Complex query: Count the number of people who have ordered all types of dishes (all items from the menu) at once.

    The backend implementation for this application can be found in the "olsheden_semestral" folder.