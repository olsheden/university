package TJV.olsheden_semestral.repository;

import TJV.olsheden_semestral.domain.Restaurant;
import TJV.olsheden_semestral.dtos.RestaurantDto;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface RestaurantRepository extends JpaRepository<Restaurant, Long> {
}
