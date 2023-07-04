package TJV.olsheden_semestral.service;

import TJV.olsheden_semestral.Exception.FieldsCannotBeEmpty;
import TJV.olsheden_semestral.Exception.InvalidStateException;
import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.domain.Restaurant;
import TJV.olsheden_semestral.repository.RestaurantRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Collection;
import java.util.Optional;

@Service
public class RestaurantService {

    @Autowired
    private RestaurantRepository restaurantRepository;

    public RestaurantService(RestaurantRepository restaurantRepository) {
        this.restaurantRepository = restaurantRepository;
    }

    public Restaurant create(Restaurant restaurant) throws FieldsCannotBeEmpty,  InvalidStateException {
        Long id = restaurant.getId();
        if(id != null && restaurantRepository.existsById(id))
            throw new InvalidStateException("Invalid state of order");
        if(restaurant.getAddress() == null || restaurant.getName() == null)
            throw new FieldsCannotBeEmpty("You should fill all the restaurant's fields");
        return restaurantRepository.save(restaurant);
    }

    public Optional<Restaurant> readById(Long id){
        return restaurantRepository.findById(id);
    }

    public Collection<Restaurant> readAll() {
        return restaurantRepository.findAll();
    }

    public Restaurant update(Restaurant restaurant) throws NotFoundException, FieldsCannotBeEmpty {
        if (restaurantRepository.findById(restaurant.getId()).isEmpty()){
            throw new NotFoundException("Restaurant not found");
        }
        return restaurantRepository.save(restaurant);
    }

    public void deleteById(Long id) throws NotFoundException {

        if (restaurantRepository.findById(id).isEmpty())
            throw new NotFoundException("Restaurant not found");

        restaurantRepository.deleteById(id);

    }
}