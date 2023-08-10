 void deleteInactiveTenants() {
        // Assuming Tenant has a method isActive() to check activity status
        // and TenantDao has a method to remove a tenant.
        for (int i = 0; i < tenantDao->list->getSize(); i++) {
            Tenant tenant = tenantDao->list->get(i);
            if (!tenant.isActive()) {
                tenantDao->list->remove(i);
                std::cout << "Deleted tenant: " << tenant.getUsername() << std::endl;
            }
        }
    }

void summarizeTop10FavoriteProperties() {
// Assuming there's a method in PropertyDao to fetch property details using property IDs
// For simplicity, using a map to count favorite properties. This can be refined further.
std::map<int, int> propertyFavoritesCount; // <propertyId, count>

// Counting favorites for each property
for (int i = 0; i < tenantDao->list->getSize(); i++) {
    Tenant tenant = tenantDao->list->get(i);
    auto favorites = tenant.getFavoriteProperties(); // Assuming this method exists
    for (int propId : favorites) {
        propertyFavoritesCount[propId]++;
    }
}

 void manageTenancyRequests() {
        // Assuming a RentRequestDao class exists with methods to fetch and update rent requests
        // The manager can then approve or reject these requests.
        // This is a stubbed out version and can be expanded with actual data structures and logic.

        std::cout << "Displaying Rent Requests:" << std::endl;
        // Fetch all rent requests using RentRequestDao
        // This is just a placeholder to show the logic flow
        std::vector<RentRequest> rentRequests; // Assuming RentRequest class exists
        // rentRequests = rentRequestDao->fetchAllRentRequests();

        // Display rent requests with details and allow manager to approve or reject
        for (const RentRequest &request : rentRequests) {
            std::cout << "Property: " << request.getPropertyName() << ", Tenant: " << request.getTenantName() << std::endl;
            std::cout << "Duration: " << request.getRentDuration() << " months" << std::endl;
            std::cout << "Approve (Y/N)? ";
            char choice;
            std::cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                // Assuming a method to approve the request in RentRequestDao
                // rentRequestDao->approveRentRequest(request);
                std::cout << "Rent request approved." << std::endl;
            } else {
                // Assuming a method to reject the request in RentRequestDao
                // rentRequestDao->rejectRentRequest(request);
                std::cout << "Rent request rejected." << std::endl;
            }
        }
    }

    void managePayments() {
        // Assuming a PaymentDao class exists which can handle payment confirmations
        // This method would allow the manager to confirm payments for confirmed tenancies.
        // This is a stubbed out version and can be expanded with actual data structures and logic.

        std::cout << "Displaying Pending Payments:" << std::endl;
        // Fetch all pending payments using PaymentDao
        // This is just a placeholder to show the logic flow
        std::vector<Payment> pendingPayments; // Assuming Payment class exists
        // pendingPayments = paymentDao->fetchPendingPayments();

        // Display pending payments with details and allow manager to confirm
        for (const Payment &payment : pendingPayments) {
            std::cout << "Tenant: " << payment.getTenantName() << ", Amount: " << payment.getAmount() << " RM" << std::endl;
            std::cout << "Confirm Payment (Y/N)? ";
            char choice;
            std::cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                // Assuming a method to confirm payment in PaymentDao
                // paymentDao->confirmPayment(payment);
                std::cout << "Payment confirmed." << std::endl;
            }
        }
    }