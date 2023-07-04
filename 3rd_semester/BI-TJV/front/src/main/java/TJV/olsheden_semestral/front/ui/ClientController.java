package TJV.olsheden_semestral.front.ui;

import TJV.olsheden_semestral.front.domain.ClientDto;
import TJV.olsheden_semestral.front.service.ClientService;
import TJV.olsheden_semestral.front.service.OrderService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.ModelAndView;

import javax.validation.Valid;
import javax.ws.rs.BadRequestException;
import javax.ws.rs.PUT;

@Controller
@RequestMapping("/clients")
public class ClientController {
    private ClientService clientService;

    private OrderService orderService;

    public ClientController(ClientService clientService, OrderService orderService) {
        this.clientService = clientService;
        this.orderService = orderService;
    }

    @GetMapping
    public String listClients(Model model) {
        model.addAttribute("allClients", clientService.readAll());
        return "clients";
    }

    @GetMapping ("/add")
    public String addClient(Model model) {
        ClientDto client = new ClientDto();
        model.addAttribute("client", client);
        return "addClient";
    }

    @PostMapping ("/add")
    public String addClientSubmit(@ModelAttribute ClientDto client, Model model) {
        clientService.create(client);
        model.addAttribute("client", client);
        return "redirect:/clients";
    }

    @GetMapping("/edit/{id}")
    public String editClient(@PathVariable long id, Model model) {
        clientService.setCurrentClient(id);
        model.addAttribute("client", clientService.readOne().orElseThrow());
        return "clientEdit";
    }

    @PostMapping("/edit")
    public String editClientSubmit(@ModelAttribute ClientDto client, Model model) {
        clientService.setCurrentClient(client.id);
        try {
            clientService.update(client);
        } catch (BadRequestException e) {
            model.addAttribute("error", true);
            model.addAttribute("errormsg", e.getMessage());
        }
        model.addAttribute("client", client);
        return "redirect:/clients";
    }

    @GetMapping("/delete/{id}")
    public String deleteClient(@PathVariable Long id){
        clientService.setCurrentClient(id);
        clientService.deleteOne();
        return "redirect:/clients";
    }

    @GetMapping("/count")
    public String countClientsWithAllProducts(Model model){
        Long count = orderService.countCustomersWithAllProductTypes();
        model.addAttribute("count", count);
        model.addAttribute("allClients", clientService.readAll());
        return "clients";
    }
}


