package TJV.olsheden_semestral.front.client_api;


import TJV.olsheden_semestral.front.domain.ClientDto;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.Entity;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;
import java.util.Arrays;
import java.util.Collection;
import java.util.Optional;

@Component
public class ClientClient {
    private WebTarget allClientEndpoint;
    private WebTarget singleEndpointTemplate;
    private WebTarget singleClientEndpoint;

    public ClientClient(@Value("${server.url}") String apiUrl) {
        var c = ClientBuilder.newClient();
        allClientEndpoint = c.target(apiUrl + "/clients");
        singleEndpointTemplate = allClientEndpoint.path("/{id}");
    }

    public ClientDto create(ClientDto e) {
        return allClientEndpoint.request(MediaType.APPLICATION_JSON_TYPE)
                .post(Entity.entity(e, MediaType.APPLICATION_JSON_TYPE), ClientDto.class);
    }

    public Collection<ClientDto> readAll() {
        var res = allClientEndpoint.request(MediaType.APPLICATION_JSON_TYPE)
                .get(ClientDto[].class);
        return Arrays.asList(res);
    }

    public Optional<ClientDto> readOne() {
        var response = singleClientEndpoint.request(MediaType.APPLICATION_JSON_TYPE).get();
        if (response.getStatus() == 200)
            return Optional.of(response.readEntity(ClientDto.class));
        else if (response.getStatus() == 404) {
            return Optional.empty();
        } else
            throw new RuntimeException(response.getStatusInfo().getReasonPhrase());
    }

    public void setCurrentClient(long id) {
        singleClientEndpoint = singleEndpointTemplate.resolveTemplate("id", id);
    }

    public void updateOne(ClientDto e) {
        singleClientEndpoint.request(MediaType.APPLICATION_JSON_TYPE).put(Entity.entity(e, MediaType.APPLICATION_JSON_TYPE));
    }

    public void deleteOne() {
        singleClientEndpoint.request(MediaType.APPLICATION_JSON_TYPE).delete();
    }

}

