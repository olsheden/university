package TJV.olsheden_semestral.front.ui;


import TJV.olsheden_semestral.front.domain.RestaurantDto;
import TJV.olsheden_semestral.front.service.RestaurantService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import javax.ws.rs.BadRequestException;

@Controller
@RequestMapping("/restaurants")
public class RestaurantController {
    private RestaurantService restaurantService;

    public RestaurantController(RestaurantService restaurantService) {
        this.restaurantService = restaurantService;
    }

    @GetMapping
    public String listRestaurants(Model model) {
        model.addAttribute("allRestaurants", restaurantService.readAll());
        return "restaurants";
    }

    @GetMapping ("/add")
    public String addRestaurant(Model model) {
        RestaurantDto restaurant = new RestaurantDto();
        model.addAttribute("restaurant", restaurant);
        return "addRestaurant";
    }

    @PostMapping ("/add")
    public String addRestaurantSubmit(@ModelAttribute RestaurantDto restaurant, Model model) {
        restaurantService.create(restaurant);
        model.addAttribute("restaurant", restaurant);
        return "redirect:/restaurants";
    }

    @GetMapping("/edit/{id}")
    public String editRestaurant(@PathVariable long id, Model model) {
        restaurantService.setCurrentRestaurant(id);
        model.addAttribute("restaurant", restaurantService.readOne().orElseThrow());
        return "restaurantEdit";
    }

    @PostMapping("/edit")
    public String editRestaurantSubmit(@ModelAttribute RestaurantDto restaurant, Model model) {
        restaurantService.setCurrentRestaurant(restaurant.id);
        try {
            restaurantService.update(restaurant);
        } catch (BadRequestException e) {
            model.addAttribute("error", true);
            model.addAttribute("errormsg", e.getMessage());
        }
        model.addAttribute("restaurant", restaurant);
        return "redirect:/restaurants";
    }

    @GetMapping("/delete/{id}")
    public String deleteRestaurant(@PathVariable Long id){
        restaurantService.setCurrentRestaurant(id);
        restaurantService.deleteOne();
        return "redirect:/restaurants";
    }
}

