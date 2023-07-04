package TJV.olsheden_semestral.repository;

import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.dtos.OrderDto;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

@Repository
public interface OrderReposiroty extends JpaRepository<Order, Long> {
    @Query("SELECT COUNT(DISTINCT o.client) FROM Order o WHERE :productType1 member of o.product_type AND :productType2 member of o.product_type AND :productType3 member of o.product_type")
    Long countClientsWithAllProducts(@Param("productType1") String productType1, @Param("productType2") String productType2, @Param("productType3") String productType3);
}
