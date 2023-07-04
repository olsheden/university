package TJV.olsheden_semestral.front.ui;



import TJV.olsheden_semestral.front.domain.OrderDto;
import TJV.olsheden_semestral.front.service.OrderService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import javax.ws.rs.BadRequestException;

@Controller
@RequestMapping("/orders")
public class OrderController {
    private OrderService orderService;

    public OrderController(OrderService orderService) {
        this.orderService = orderService;
    }

    @GetMapping
    public String listOrders(Model model) {
        model.addAttribute("allOrders", orderService.readAll());
        return "orders";
    }

    @GetMapping ("/add")
    public String addOrder(Model model) {
        OrderDto order = new OrderDto();
        model.addAttribute("order", order);
        return "addOrder";
    }

    @PostMapping ("/add")
    public String addOrderSubmit(@ModelAttribute OrderDto order, Model model) {
        orderService.create(order);
        model.addAttribute("order", order);
        return "redirect:/orders";
    }

    @GetMapping("/edit/{id}")
    public String editOrder(@PathVariable long id, Model model) {
        orderService.setCurrentOrder(id);
        model.addAttribute("order", orderService.readOne().orElseThrow());
        return "orderEdit";
    }

    @PostMapping("/edit")
    public String editOrderSubmit(@ModelAttribute OrderDto order, Model model) {
        orderService.setCurrentOrder(order.id);
        try {
            orderService.update(order);
        } catch (BadRequestException e) {
            model.addAttribute("error", true);
            model.addAttribute("errormsg", e.getMessage());
        }
        model.addAttribute("order", order);
        return "redirect:/orders";
    }

    @GetMapping("/delete/{id}")
    public String deleteOrder(@PathVariable Long id){
        orderService.setCurrentOrder(id);
        orderService.deleteOne();
        return "redirect:/orders";
    }
}


