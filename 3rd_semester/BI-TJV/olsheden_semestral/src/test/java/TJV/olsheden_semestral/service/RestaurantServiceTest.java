package TJV.olsheden_semestral.service;

import TJV.olsheden_semestral.Exception.FieldsCannotBeEmpty;
import TJV.olsheden_semestral.Exception.InvalidStateException;
import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.domain.Restaurant;
import TJV.olsheden_semestral.repository.ClientRepository;
import TJV.olsheden_semestral.repository.RestaurantRepository;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.testng.annotations.Test;

import java.util.Collections;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.verify;
import static org.hamcrest.Matchers.any;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

@SpringBootTest
 public class RestaurantServiceTest{


    @MockBean
    private RestaurantRepository restaurantRepository;

    @Test
    public void testCreate() throws Exception {
        RestaurantRepository mockRestaurantRepository = mock(RestaurantRepository.class);

        Restaurant expectedRestaurant = new Restaurant();
        when(mockRestaurantRepository.save(expectedRestaurant)).thenReturn(expectedRestaurant);

        RestaurantService testClass = new RestaurantService(mockRestaurantRepository);

        Restaurant actualRestaurant = testClass.create(expectedRestaurant);

        assertEquals(expectedRestaurant, actualRestaurant);

        verify(mockRestaurantRepository).save(expectedRestaurant);
    }

    @Test
    public void testReadById() {
        RestaurantRepository mockRestaurantRepository = mock(RestaurantRepository.class);

        when(mockRestaurantRepository.findById(1L)).thenReturn(Optional.of(new Restaurant()));

        RestaurantService testClass = new RestaurantService(mockRestaurantRepository);

        testClass.readById(1L);

        verify(mockRestaurantRepository).findById(1L);
    }

    @Test
    public void testReadAll() {
        RestaurantRepository mockRestaurantRepository = mock(RestaurantRepository.class);

        when(mockRestaurantRepository.findAll()).thenReturn(Collections.emptyList());

        RestaurantService testClass = new RestaurantService(mockRestaurantRepository);

        testClass.readAll();

        verify(mockRestaurantRepository).findAll();
    }

    @Test
    public void testUpdate() throws Exception {
        RestaurantRepository mockRestaurantRepository = mock(RestaurantRepository.class);

        Restaurant expectedRestaurant = new Restaurant();
        when(mockRestaurantRepository.findById(1L)).thenReturn(Optional.of(expectedRestaurant));
        when(mockRestaurantRepository.save(expectedRestaurant)).thenReturn(expectedRestaurant);

        RestaurantService testClass = new RestaurantService(mockRestaurantRepository);

        testClass.update(new Restaurant());

        verify(mockRestaurantRepository).save(expectedRestaurant);
    }

    @Test
    public void testDeleteById() throws Exception {
        // Create a mock RestaurantRepository
        RestaurantRepository mockRestaurantRepository = mock(RestaurantRepository.class);

        // Define the expected behavior of the mock RestaurantRepository
        when(mockRestaurantRepository.findById(1L)).thenReturn(Optional.of(new Restaurant()));

        // Create an instance of the class that you are testing
        RestaurantService testClass = new RestaurantService(mockRestaurantRepository);

        // Call the deleteById() method
        testClass.deleteById(1L);

        // Verify that the mock RestaurantRepository's deleteById() method was called
        verify(mockRestaurantRepository).deleteById(1L);
    }

@Test
    public void testCreate_FieldsCannotBeEmpty() {
        RestaurantRepository mockRestaurantRepository = mock(RestaurantRepository.class);

        RestaurantService testClass = new RestaurantService(mockRestaurantRepository);

        Restaurant restaurant = new Restaurant();
        restaurant.setId(1L);
        restaurant.setAddress("");
        restaurant.setName("");

        assertThrows(FieldsCannotBeEmpty.class, () -> testClass.create(restaurant));
    }

    @Test
    public void testCreate_InvalidStateException() {
        RestaurantRepository mockRestaurantRepository = mock(RestaurantRepository.class);

        when(mockRestaurantRepository.existsById(1L)).thenReturn(true);

        RestaurantService testClass = new RestaurantService(mockRestaurantRepository);
        Restaurant restaurant = new Restaurant();
        restaurant.setId(1L);
        restaurant.setAddress("123 Main St");
        restaurant.setName("Test Restaurant");

        assertThrows(InvalidStateException.class, () -> testClass.create(restaurant));
    }

    @Test
    public void testUpdate_NotFoundException() {
        RestaurantRepository mockRestaurantRepository = mock(RestaurantRepository.class);

        when(mockRestaurantRepository.findById(1L)).thenReturn(Optional.empty());

        RestaurantService testClass = new RestaurantService(mockRestaurantRepository);

        Restaurant restaurant = new Restaurant();
        restaurant.setId(1L);
        restaurant.setAddress("123 Main St");
        restaurant.setName("Test Restaurant");

        assertThrows(NotFoundException.class, () -> testClass.update(restaurant));
    }

    @Test
    public void testUpdate_FieldsCannotBeEmpty() {
        RestaurantRepository mockRestaurantRepository = mock(RestaurantRepository.class);

        when(mockRestaurantRepository.findById(1L)).thenReturn(Optional.of(new Restaurant()));

        RestaurantService testClass = new RestaurantService(mockRestaurantRepository);

        Restaurant restaurant = new Restaurant();
        restaurant.setId(1L);
        restaurant.setAddress("");
        restaurant.setName("");

        assertThrows(FieldsCannotBeEmpty.class, () -> testClass.update(restaurant));
    }
}
