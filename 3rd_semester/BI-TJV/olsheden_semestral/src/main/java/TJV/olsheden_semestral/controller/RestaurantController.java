package TJV.olsheden_semestral.controller;

import TJV.olsheden_semestral.Exception.AlreadyExistsException;
import TJV.olsheden_semestral.Exception.FieldsCannotBeEmpty;
import TJV.olsheden_semestral.Exception.InvalidStateException;
import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.domain.Restaurant;
import TJV.olsheden_semestral.dtos.OrderDto;
import TJV.olsheden_semestral.dtos.RestaurantDto;
import TJV.olsheden_semestral.service.RestaurantService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Collection;
import java.util.HashSet;
import java.util.function.Function;
import java.util.stream.StreamSupport;

@RestController
@RequestMapping("/restaurants")
public class RestaurantController {

    @Autowired
    private final RestaurantService restaurantService;

    @Autowired
    private final Function<RestaurantDto, Restaurant> restaurantConverterToEntity;

    @Autowired
    private final Function<Restaurant, RestaurantDto> restaurantConverterToDto;

    public RestaurantController(RestaurantService restaurantService, Function<RestaurantDto, Restaurant> restaurantConverterToEntity, Function<Restaurant, RestaurantDto> restaurantConverterToDto) {
        this.restaurantService = restaurantService;
        this.restaurantConverterToEntity = restaurantConverterToEntity;
        this.restaurantConverterToDto = restaurantConverterToDto;
    }

    @PostMapping
    public RestaurantDto createRestaurant(@RequestBody RestaurantDto restaurantDto) throws FieldsCannotBeEmpty, InvalidStateException {
        return restaurantConverterToDto.apply(restaurantService.create(restaurantConverterToEntity.apply(restaurantDto)));
    }


    @GetMapping("/{id}")
    public ResponseEntity<RestaurantDto> readOne(@PathVariable Long id) throws NotFoundException {
        var result = restaurantService.readById(id);
        if (result.isPresent())
            return ResponseEntity.ok(restaurantConverterToDto.apply(result.get()));
        else
            return ResponseEntity.notFound().build();

    }

    @GetMapping
    public Collection<RestaurantDto> readAll(){
        return StreamSupport.stream(restaurantService.readAll().spliterator(),false).map(restaurantConverterToDto).toList();
    }

    @PutMapping("/{id}")
    public void updateRestaurant(@RequestBody RestaurantDto restaurantDto, @PathVariable Long id) throws NotFoundException, AlreadyExistsException, FieldsCannotBeEmpty {
        restaurantService.update(restaurantConverterToEntity.apply(restaurantDto));
    }

    @DeleteMapping("/{id}")
    public void deleteRestaurant(@PathVariable Long id) throws NotFoundException {
        restaurantService.deleteById(id);
    }
}

